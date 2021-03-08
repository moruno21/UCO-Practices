#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> //Para el PID del main()

#define N 5
//Prototipos
void * message_print (void *); 


int main(void) 
{
	int error = 0;
	size_t i = 0;
	char mess[] = "Esto es una prueba"; 
	// Declaracion de un Array de hebras  
	pthread_t thr[N]; 

	for(i = 0; i < N; i++)
	{
	  error = pthread_create( &(thr[i]), NULL, message_print, (void *) mess); 
	  /* Manejar el error */
	  //...COMPLETAR
	}

	printf("Soy el main() con PID %d, He creado las hebras, saliendo...\n", getpid()); 

	/* La siguiente línea permite que terminen hebras que han invocado a pthread_detach().
     Comentela y ejecute varias veces. Observe lo ocurrido.*/
	pthread_exit(NULL);
}


void * message_print (void * ptr) 
{
    int error = 0; 
    char *msg;

    /* Desconexión del hilo cuando finalice. 
       pthread_self() devuelve el ID de la hebra que invoca esta función*/
    error = pthread_detach(pthread_self());
    /* Manejar el error */ 
	//... COMPLETAR

    msg = (char *) ptr;
    printf("Soy la hebra %lu, valor de mess: %s\n", (unsigned long) pthread_self(), msg); 
    pthread_exit(NULL);
}
