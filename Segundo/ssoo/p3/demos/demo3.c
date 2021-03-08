/*
Este programa crea dos hilos. Cada hilo hace exactamente lo mismo, incrementar una variable
global un numero de veces "NITER". El resultado final debe ser el doble del numero de veces que se
incrementa la variable, ya que cada hilo la incrementa el mismo número de veces. 

Si no hubiera semáforo general, el resultado podría ser inconsistente.

*/

#include <pthread.h> 
#include <semaphore.h>
#include <errno.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.

#define NITER 100 

int count = 0; //Recurso compartido
sem_t mutex; //Semaforo general

void * ThreadAdd(void *a) 
{
    int i, tmp,p;
    
    for(i = 0; i < NITER; i++) 
    {
        p = sem_wait(&mutex); //Chequeo para ver si el semáforo está abierto despues de decrementar. 
        if (p !=0)
        {
             printf("sem_wait error...\n");
             printf("errno value= %d definido como %s\n", errno, strerror(errno));
             pthread_exit(NULL);
        }
        
        /*
        ¿ Por que no poner count++ ?
        Es para simular que el simple incremento de una variable podría estar compuesto a nivel ensamblador
        de varias instrucciones e incluso involucrar a la ALU, por lo que el hilo se podria ver interrumpido
        o sacado de la CPU antes de realizar todas las instrucciones que dieran lugar al incremento.
        En este caso podriamos suponer que el proceso puede salir despues de la sentencia tmp = count;
        con lo que el valor de count podria ser inconsistente en count = tmp; si algún otro hilo modifica
        mientras el actual esta fuera de la CPU.
        */
        tmp = count;  //Seccion Critica
        tmp = tmp+1; //Seccion Critica
        count = tmp; //Seccion Critica
        
        p = sem_post(&mutex); //Se comprueba el valor del semáforo al incrementarlo. Si hay algun proceso en cola pasa a estado Listo. 
        if (p !=0)
        {
             printf("sem_post error...\n");
             printf("errno value= %d definido como %s\n", errno, strerror(errno));
             pthread_exit(NULL);
        }
    } 
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) 
{
	pthread_t tid1, tid2;
	int p;
	
	//Inicializamos nuestro semáforo a 1
	//y el cero indica que el semáforo solo
	//estara disponible para este main() y sus hilos(). 
	p = sem_init(&mutex, 0, 1);
	if (p !=0)
   {
       printf("sem_init error...\n");
       printf("errno value= %d definido como %s\n", errno, strerror(errno));
       exit(EXIT_FAILURE);
   }

	//Note que podría hacer lo siguiente con un bucle for() en vez de repetir codigo. Modifiquelo.
	if(pthread_create(&tid1, NULL, ThreadAdd, NULL)) 
	{
      printf("\n ERROR creating thread 1");
      exit(EXIT_FAILURE); 
	}
	if(pthread_create(&tid2, NULL, ThreadAdd, NULL)) 
	{
	  printf("\n ERROR creating thread 2");
	  exit(EXIT_FAILURE); 
	}

	//Note que podría hacer esto con un bucle for(). Modifiquelo.
	if(pthread_join(tid1, NULL)) /* wait for the thread 1 to finish */ 
	{
      printf("\n ERROR joining thread");
      exit(EXIT_FAILURE); 
	}
	if(pthread_join(tid2, NULL)) /* wait for the thread 2 to finish */ 
	{
      printf("\n ERROR joining thread");
      exit(EXIT_FAILURE); 
	}

	//Se comprueba si el valor del recurso compartido es menor o mayor del doble, que es lo que se espera.
	//Nunca entrara en el primer if al haber utilizado un semaforo para evitar inconsistencia de datos.
	if ( (count< (2 * NITER)) || (count>(2 * NITER)) )
	  printf("\nBOOM! count is [%d], should be %d\n", count, 2*NITER);
	else
	  printf("\nOK! count is [%d] \n", count);

	exit(EXIT_SUCCESS);
}
