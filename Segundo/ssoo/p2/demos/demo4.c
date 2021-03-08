#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

//Prototipos
void *mifuncion(void *);
void miFuncion2(); 

//Hilo principal
int main (void) 
{
    pthread_t tid; 
	 int misargs[2];
    
    misargs[0] = -5; 
    misargs[1] = -6;

    printf("Se va a crear un hilo...\n");
    pthread_create(&tid, NULL, mifuncion, (void *) misargs);

    /*Si comentamos la siguiente linea, puede que a la hebra no le de tiempo a ejecutarse ni siquiera parcialmente, de manera que el main() terminará y con el todas las hebras asociadas a este proceso*/ 
    printf("Hilo creado. Esperando su finalizacion con pthread_join()...\n");
    pthread_join(tid, NULL);
    printf("Proceso principal finalizado...\n");
    exit(EXIT_SUCCESS);
}


//Función asignada a hilo
void *mifuncion(void *arg) 
{
    int *argu;
    printf("Hilo hijo ejecutando...\n");
    argu = (int *) arg; //Casting a entero del parámetro de entrada. 
	 printf("Hilo hijo: arg0= %d arg1= %d\n", argu[0], argu[1]);
    printf("Hilo hijo finalizando....\n"); 
    miFuncion2();
    /*No se llegará a ejecutar de aquí hasta el final de esta función*/ 
    sleep(2);
    printf("Soy el hilo. He salido de la llamada a subrutina\n"); 
    pthread_exit(NULL);
}

//Esta funcion no es un hilo, es una subrutina
void miFuncion2() 
{
    printf("Soy el hilo creado y estoy dentro de una subrutina para invocar a pthread_exit()...\n");
    pthread_exit(NULL); //No sale del proceso pero hace que termine el hilo
}
