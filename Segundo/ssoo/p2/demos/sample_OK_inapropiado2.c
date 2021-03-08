#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/****************************************************************************************
Este ejercicio "aparentemente" funciona, pero lo que se está haciendo no va con la
filosofía y funcionamiento de los hilos con la biblioteca pthread. Por tanto, no debemos
utilizar esta metodología!!!.

Observe esto, es en lo que se basa este ejercicio:

ptr = (void *)5;
Now ptr points at the memory address 0x5
****************************************************************************************/

void * th_function (void *arg)
{
     long y = 10;
	  /* A continuación estamos devolviendo la dirección de memoria 0X10. ¿Por qué?
	  Porque le estamos haciendo un casting a puntero genérico a un tipo de dato que
	  es un entero (no es la dirección de memoria de un entero). Ese casting automá-
	  ticamente convierte el entero 10 a la dirección de memoria 0X10 */
     pthread_exit((void *)y); 
}

int main(int argn, char ** argp)
{
	  int join_value;
	  long rvalue;
	  void *ret;
     pthread_t thread;
     
     pthread_create(&thread, NULL, th_function, NULL);
	  /* Con este pthread_join() estamos asignando a ret una dirección de memoria. ¿Cuál?
	  Pues la que se devolvió con pthread_exit((void *)y), es decir, 0X10. */
     join_value=pthread_join(thread,&ret);
     
     if(join_value!=0)
	  {
		  perror("Fallo en el join...\n");		
        exit(EXIT_FAILURE);
     }

		/*Aquí viene la segunda "chapuza". Estamos haciendo un casting a long de una dirección de memoria,
		es decir, estamos convirtiendo 0X10 a 10. Por eso se muestra el resultado correcto, pero
		la metodología que hemos seguido no es correcta. Si en vez de enteros se usasen floats, la salida
		ya ni se mostraría falsamente correcta */
		rvalue = (long)ret;
	   printf("Proceso o hilo principal, el valor devuelto por la hebra es: %ld\n", rvalue);

	  
     exit(EXIT_SUCCESS);
}
