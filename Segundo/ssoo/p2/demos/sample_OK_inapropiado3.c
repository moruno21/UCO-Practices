#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************************
 Por lo mismo que se ha explicado en el ejercicio "sample_OK2_inapropiado.c" este ejemplo muestra la salida
correcta pero su implementación no es la apropiada. Por tanto no debemos programar con hebras
de esta manera. Con datos de tipo float ya no obtendría la salida aparentemente correcta.
Comparelo con  "sample_OK2_inapropiado.c".
**********************************************************************************************/

void * th_function (void *arg)
{
        long y = 10;
        
        pthread_exit((void *)y); 
}

int main(int argn, char ** argp)
{
	int join_value;
	long rvalue;
	long *ret; 
	pthread_t thread;

	pthread_create(&thread, NULL, th_function, NULL);
	
	join_value = pthread_join(thread,(void **) &ret); 


	if(join_value!=0)
	{
	  perror("Fallo en el join...\n");		
	  exit(EXIT_FAILURE);
	}
   
	rvalue = (long)ret; 
	printf("Proceso o hilo principal, el valor devuelto por la hebra es: %ld\n", rvalue);
	 
	exit(EXIT_SUCCESS);
}
