#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> //Para el PID del main()

#define N 5

void * message_print (void *);

int main(void) 
{
    int error = 0;
    int i = 0;
    int j;
    int mess[N];
    
    /* Creación de un Array de hebras */ 
    pthread_t thr [N]; 
    
    //Inicializacion del vector de enteros mess
    for(i=0;i<N;i++) 
		mess[i]=i+1;
    
    for(i = 0; i < N; i++) 
	 {
        error = pthread_create( &(thr[i]), NULL, message_print, (void *) &mess[i]); 
        /* Manejar el error */
        //...
    }
    
	 printf("Soy el main() con PID %d, He creado las hebras, saliendo...\n", getpid()); 
    pthread_exit(NULL);
    printf("Esta linea no se ejecuta!!!\n");
}

void * message_print (void * ptr) 
{
    int error = 0;
    /* Desconexión del hilo cuando finalice. 
	 pthread_self() devuelve el ID de la hebra que invoca esta función.*/

    error = pthread_detach(pthread_self());
    /* Manejo del error si lo hubiera */
    //...

    printf("Soy la hebra %lu, valor de mess: %d\n", (unsigned long) pthread_self(), *(int *) ptr); 
    //printf("Soy la hebra: %d\n", *(int *) ptr);
    pthread_exit(NULL); 
}

