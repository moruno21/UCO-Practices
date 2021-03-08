#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * th_function (void *arg)
{
	long * y = malloc(sizeof(long));
	*y = 10;
	/*
   A continuación estamos devolviendo un puntero a entero al que se le hace un casting a void.
	Esto significa que estaremos devolviendo la dirección de memoria de un intero cuyo contenido
   es 10. Este entero se ha reservado en el montículo del proceso o hilo principal, que es accesible
	a todas los hilos creados.
   */		 
	pthread_exit((void *)y); 
}


int main(int argn, char ** argp)
{
	int join_value;
	long rvalue;
	long *ret;
	pthread_t thread;

	pthread_create(&thread, NULL, th_function, NULL);

	/* A pthread_join() le estamos pasando por referencia como segundo parámetro la dirección
	de un puntero a entero. Al pasar la dirección de memoria de un puntero por referencia, el contenido
	de ese puntero (a donde apunta) puede ser modificado. ¿Con qué se modifica? Con la dirección de
	memoria de un entero que se devuelve en "pthread_exit((void *)y)". Por tanto, "long * ret" ahora
	apunta a donde apuntaba "long * y", solo que está casteado a void.*/
	join_value = pthread_join(thread,(void**) &ret);

	if(join_value!=0)
	{
	  perror("Fallo en pthread_join()...\n");		
	  exit(EXIT_FAILURE);
	}
	  
	rvalue = *ret; 
	printf("Proceso o hilo principal, el valor devuelto por la hebra es: %ld\n", rvalue);

	exit(EXIT_SUCCESS);
}



