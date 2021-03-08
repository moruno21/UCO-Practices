/*****************************************************************************
* FILE: hello_arg_bad_parameter.c
* DESCRIPTION:
*   This "hello world" Pthreads program demonstrates an unsafe (incorrect)
*   way to pass thread arguments at thread creation.  In this case, the
*   argument variable is changed by the main thread as it creates new threads.

This example performs argument passing incorrectly. It passes the address of variable t, 
which is shared memory space and visible to all threads. As the loop iterates, 
the value of this memory location changes, possibly before the created threads can access it. 

* AUTHOR: Blaise Barney
* Modified by Juan Carlos Fernandez Caballero
******************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para el sleep a modo divulgativo
#define NUM_THREADS 4


void *PrintHello(void *threadid)
{
   int taskid;
   
   //sleep(1);
   taskid = *(int *)threadid;
   
   printf("Hola desde la hebra %d...\n", taskid);
   
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t;

	for(t=0;t<NUM_THREADS;t++) 
	{
		printf("Creando hebra %d...\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);

		/*Pruebe a descomentar el sleep(3), posiblemente ya si obtenga la salida que usted esperaba..., pero es una mala programacion.
		Con el sleep(3) comentado, posiblemente las hebras impriman todas que su tarea es la 4, ya que al proceso principal le dará
		tiempo a crear todas las hebras antes de que una de ellas empiece a ejecutar. En este caso, todas recogeran un valor de "t" igual a 4.*/
		
		//sleep(3);   

		if (rc) 
		{
			 printf("ERROR; El codigo de error en pthread_create() es %d\n", rc);
			 exit(EXIT_FAILURE);
		}
	}
	pthread_exit(NULL);  //Necesario si la hebra no es de tipo "detach" o sino se realiza un "pthread_join()".
}
