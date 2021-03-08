#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Prototipos
void * message_print (void *);

int main(void)
{
   int error = 0;
   long aux = 7;
   char mess[] = "Esto es una prueba";
   pthread_t thr; 
   void *ret;
   
   ret = &aux;

   error = pthread_create( &thr, NULL, message_print, (void  *) mess);
   /* Manejar el error */
   //...

 	printf("Soy el main() con PID %d, he creado la hebra y el valor de mess es:\"%s\". Avanzando a pthread_join()...\n", getpid(), mess); 

   
   //sleep(1); //Descomentar si el main() llega antes para ver el resultado.

   /*
    Si el join se ejecuta una vez haya terminado la hebra detach, dará un error y el código entrará en el esquema
    
    if(error!=0)
      printf("Se ha producido un error en pthread_join()!!!\n");
    
    De esta forma, el contenido de "ret" no llega a modificarse y su valor será 7, pues ya se habrá liberado el estado,
    variables y demás de la hebra detach, por lo que la direccion de la variable "y" devuelta por la hebra, además de no ser
    recogida también desaparece.
    
    en caso contrario, es decir, si el join se ejecuta antes de que termine la hebra detach,
    el join no dará error y no entrará en el esquema de código antes mencionado, de forma que la hebra devolverá 
    la dirección de memoria de la variable "y" que reservo y se recogera por "ret" el valor 10. 
    
    CONCLUSION 1: No se debe utilizar el join con una hebra detach para evitar inconsistencias. 
    CONCLUSION 2: No se debe devolver nada de una hebra que invoca a pthread_detach()
   */
   
   error=pthread_join(thr,(void **) &ret);
   if(error!=0)
      printf("Se ha producido un error en pthread_join()\n");
   
   
   printf("Soy el main() Soy el main() con PID %d. Valor de retorno de la hebra: %ld\n",getpid(), *(long *)ret);
   pthread_exit(NULL);
}

void * message_print (void * ptr)
{
   long * y = malloc(sizeof(long));
   *y = 10;
   int error = 0;
   char *mess;

   /* Desconexión del hilo cuando finalice.
	   pthread_self() devuelve el ID de la hebra que invoca esta función.*/
   error = pthread_detach(pthread_self());
   if(error!=0)
       printf("Se ha producido un error en pthread_detach()\n");
   // Complételo con las macros de error convenientes
   //...

   mess = (char *) ptr;
   printf("Soy la hebra %lu, el valor de mess es:\"%s\"\n", (unsigned long) pthread_self(), mess); 

   pthread_exit((void *)y);
}
