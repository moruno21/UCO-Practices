//ej4.c
//Este programa crea dos hebras que incrementan una misma variable global
//Puede ser que salga 20000 correctamente, pero lo normal es que las hebra se "pisen" entre si y salga un valor distinto a 20000
//Lo de entrar critica y salir critica son semaforos que tenemos que añadir si queremos que el ejercicio funcione correctamente (practica 3)

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

int global = 0;                         //Declaramos la variable global

void * incrementar(){
    printf("Hola soy la hebra %lu\n", pthread_self());
    for (int i=0; i<10000; i++){        //Incrementamos global 10000 veces
        //entrar critica
        global++;
        //salir critica
    }
    printf("La variable global tras el incremento de la hebra vale %d\n", global);
    pthread_exit(NULL);
}

int main(int argc, const char* argv[]){
    printf("A continuacion se crearan dos hebras las cuales incrementaran 10000 una misma variable global\n");
    
    pthread_t thread[2];                //Se crea el vector para almacenar la direccion de las hebras
    
    for(int i=0; i<2; i++){
        if (pthread_create(&thread[i], NULL, (void *) incrementar, NULL)){
            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<2; i++){
        if(pthread_join(thread[i], NULL)){
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("La variable global tras la creacion e incremento de ambas hebras vale %d\n", global);      //Imprimimos por pantalla el valor de la variable global tras ser incrementada
    exit(EXIT_SUCCESS);

}