/*
Programa que imprime un supuesto valor devuelto por una hebra y asignado a un long en el hijo principal.
Observe la salida y saque las conclusiones oportunas.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * th_function (void *arg)
{
     long y = 10;
	  /*Tenemos que devolver un puntero, es decir, una direccion de memoria a un tipo de dato,
	  y castearla a void * */
     pthread_exit((void *)&y); 
}

int main(int argn, char ** argp)
{
	int join_value;
	long rvalue;
	long *ret; //No inicializado, continene basura
	pthread_t thread;

	pthread_create(&thread, NULL, th_function, NULL);

	//Recogemos el resultado devuelto por  pthread_exit() en ret.
   join_value = pthread_join(thread,(void**) &ret);
	if(join_value!=0)
	{
	  perror("Fallo en pthread_join()...\n");		
	  exit(EXIT_FAILURE);
	}

	rvalue = *ret; 
	printf("Proceso o hilo principal, el valor devuelto por la hebra es (basura): %ld\n", rvalue);
	  
	exit(EXIT_SUCCESS);
}
