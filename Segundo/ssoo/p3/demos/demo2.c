/******************************************* 
 Ejemplo de productor-consumidor
 Modified from Michael Kerrisk's code, 2014. 
 Modified from Juan Carlos Fernández, 2020.
 ********************************************/ 
/*

Modifique este ejercicio declarando el mutex en el main() en vez de hacerlo de manera global

*/
 
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {FALSE=0, TRUE=1} booleano; 

int avail = 0; //Critical section
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //Mutex


void * threadFunc(void *arg) 
{
    int cnt = atoi((char *) arg); 
	 int s, j;

    for (j=0; j<cnt; j++)
    {
        //Lock the mutex
        s = pthread_mutex_lock(&mtx); 
        if (s != 0) /*Minimo control de errores*/
        {
            printf("mutex_lock error...\n");
            pthread_exit(NULL); 
        }    

        /* Let consumer know another unit is available */ 
        avail++; /*Critical section*/
        printf("avail variable increased by thread %lu, avail=%d\n", (unsigned long) pthread_self(),avail); 
        
        //Unlock mutex
        s = pthread_mutex_unlock(&mtx);
        if (s != 0)  /*Minimo control de errores*/
        {
				printf("mutex_unlock error...\n");
				pthread_exit(NULL); 
		  }	
    }
    pthread_exit(NULL); 
}

int main(int argc, char *argv[]) 
{
    if(argc<3) 
	 {
        printf("Ussage: ./a.out Number_of_increasing_for_thread1 Number_of_increasing_for_thread2 Number_of_increasing_for_threadN\n");
        exit(EXIT_FAILURE); 
    }

    /* Creación de un Array de hebras. En este caso se usara malloc() para la cantidad de hebras a crear*/ 
    pthread_t *thr;
    int s, j;
    int totThreads;
    int totRequired; /* Total number of units that all threads will produce */
    int numConsumed; /* Total units so far consumed */
    booleano done;
    
    // El numero de hebras a crear sera el numero de argumentos menos uno
    totThreads = argc-1;
    
    thr= (pthread_t *) malloc ((totThreads)*sizeof(pthread_t));
    
    /* Create all threads */ 
    totRequired = 0;
    for (j = 0; j < totThreads; j++) 
    {
        totRequired += atoi(argv[j+1]); //Sum is the total of increments 
        
        /* Se pasa a cada hebra el numero de incrementos asignados a la misma sobre la variable compartida avail
        OJO!!!!, se esta pasando la dirección de una cadena (aunque sea un numero). Habra que reconvertir en la 
        hebra con la funcion atoi() */
        s=pthread_create(&thr[j], NULL, threadFunc, argv[j+1]);  
        if (s != 0) /*Minimo control de errores*/
        {
           printf("pthread_create error...\n");
           exit(EXIT_FAILURE);
        } 
    }
    
    printf("Main thread. Total items for decreasing = %d\n", totRequired);
    /* Use a polling loop to check for available units */ 
    numConsumed = 0;
    done = FALSE;
    for (;;) //Continuous simulation 
    {
        //Lock mutex
        s = pthread_mutex_lock(&mtx);
        if (s != 0) /*Minimo control de errores*/
        {
            printf("mutex_lock error...\n");
            exit(EXIT_FAILURE);
        }
        
        /*Critical section*/
        while (avail > 0) /* Consume all available units */ 
        {
            /* Do something with produced unit */
            numConsumed ++;
            avail--;
            printf("Main thread, decreasing avail=%d, numConsumed=%d\n", avail, numConsumed);
            
            if((numConsumed >= totRequired)) 
                done=TRUE; //enumeracion definida en la zona de variables globales
            else 
					 done=FALSE; 
        }
    
       
        /* Una vez el main() ha consumido todo lo disponible en avail desbloquea el mutex
           para que otra hebra pueda realizar nuevos incrementos que poder consumir */
        s = pthread_mutex_unlock(&mtx); /*Desbloqueo de la barrera*/ 
        if (s != 0) /*Minimo control de errores*/
        {
            printf("mutex_unlock error...\n"); 
            exit(EXIT_FAILURE);
        }    
    
        if (done)
        {
            printf("Main thread. Exiting...The %d items produced have been consumed\n", totRequired); 
            break;
        }
        else
            printf("Main thread. Unproductive time..., avail is <= 0\n");
    }
    
    
    for (j = 0; j < (argc-1); j++) 
    {
         s = pthread_join(thr[j], NULL);
         if (s != 0) /*Minimo control de errores*/
         {
            printf("pthread_join error...\n");
            exit(EXIT_FAILURE);
         }
    }
        
    exit(EXIT_SUCCESS);
}
