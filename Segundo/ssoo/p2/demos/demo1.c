#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

//Declaración de una estructura 
struct param
{
    char frase[30];
    int numero; 
	float altura;
};

/*Función que se asignará a los hilos que se creen. Recibe un puntero a estructura */ 
void *hiloMensaje (void * mensa)
{

   printf("%s %d %f\n", ((struct param *) mensa)->frase, ((struct param *) mensa)->numero, ((struct param *) mensa)->altura); 
	//La linea anterior se puede sustituir por estas otras
	/*struct param *aux = (struct param *) mensa; 
	  printf("%s %d\n", aux->frase, aux->numero);*/ 
	pthread_exit(NULL); //Fin de la hebra sin devolver nada
}

int main() //Al main se le llama hijo principal
{    
	//Declaración de dos hebras, hilos o procesos ligeros. NO CREACION 
	pthread_t thd1, thd2, thd3; 

	// Inicializacion de 2 estructuras de tipo “struct param”
	struct param param1 = {"Soy el hilo ", 1, 1.85};
	struct param param2 = {"Soy el hilo ", 2, 1.72};
	struct param param3 = {"Soy el hilo ", 3, 1.80};

	/*Creamos dos hilos. La función la pasaremos como (void *) nombreFuncion. Es decir, hacemos un casting a (void *), aunque por defecto no es necesario, ya que el nombre de una función es su dirección de memoria. También es importante realizar esto con la dirección de memoria de la variable que contiene los parámetros que se le pasan a la función */
	pthread_create (&thd1, NULL, (void *) hiloMensaje, (void *) &param1); 
	pthread_create (&thd2, NULL, (void *) hiloMensaje, (void *) &param2);
	pthread_create (&thd3, NULL, (void *) hiloMensaje, (void *) &param3);

	/*Esperamos la finalización de los hilos. Si la función devolviera algo habría que recogerlo con el segundo argumento, que en este caso esta a NULL. Cuando el segundo argumento no es NULL, se recogen los resultados que vienen de pthread_exit(), que se explicará en las siguientes demos.*/
	pthread_join(thd1, NULL); 
	pthread_join(thd2, NULL);
	pthread_join(thd3, NULL);

	/*Si no se ponen estos join() en el programa principal y simplemente lanzamos los dos hilos y finalizamos, lo más probable es que los hilos no lleguen a ejecutarse completamente o incluso que no lleguen ni a empezar antes de que el programa principal termine.*/
	printf("Han finalizado las threads.\n");
	exit(EXIT_SUCCESS); 
}
