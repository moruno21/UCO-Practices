//ej1.c
//Este ejercicio creara n hebras, creando cada una de ellas 2 valores aleatorios e imprimiendo el sumatorio de todos ellos al final del programa

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>


void * valores_aleatorios(){                            //Funcion que genera y suma dos numeros aleatorios
    
    printf("Soy la hebra %lu \n", pthread_self());

    float x = (float)rand()/(float)(RAND_MAX);          //Generamos un numero aleatorio flotante
    printf("Valor de x= %f\n", x);

    float y = (float)rand()/(float)(RAND_MAX);          //Generamos un numero aleatorio flotante
    printf("Valor de y= %f\n", y);
    
    printf("Suma de la hebra actual = %f\n", x+y);

    float *z = malloc(sizeof(float));                   //Si no reservamos memoria, la variable se eliminara al finalizar la hebra y no la podremos recoger
    *z = y + x;                                         //Suma de los valores obtenidos

    pthread_exit((void*)z);                             //Salimos de la hebra devolviendo la suma de los valores generados

}

int main(){
    int n;                              //Numero de hebras a crear
    printf("Numero de hebras: ");
    scanf("%d", &n);                    //El usuario introduce el numero de hebras que quiere crear
    
    srand(time(NULL));                  //Plantamos la semilla del numero aleatorio
    
    pthread_t thread[n];                //Creamos un vector para almacenar los identificadores de los hilos

    float suma=0;                       //Establecemos que al comenzar la suma de valores valga 0
    float * sumaHebra=0;
    
    //Si no hacemos 2 for, la funcion pthread_create nos devolvera que todas las hebras tienen el mismo identificador
    
    for (int i=0; i<n; i++){            //Entraremos en el bucle tantas veces como hebras creemos
        
        if (pthread_create(&(thread[i]), NULL, (void *) valores_aleatorios, NULL)){         //Si la creacion de la hebra nos devuelve algo distinto a 0, habra ocurrido un error
            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Creacion de la hebra %d\n", i+1);

        }

    for (int i=0; i<n; i++){            //Entraremos en el bucle tantas veces como hebras creemos
        
        
        if (pthread_join(thread[i], (void **)&sumaHebra)){                                  //Si la espera de la hebra nos devuelve algo distinto a 0, habra ocurrido un error
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        suma = suma + *sumaHebra;                //Al final de cada hebra aumentamos la suma de los valores obtenidos sumandole los de la hebra recien finalizada
    }
        printf("Suma total = %f\n", suma);       //Imprimimos finalmente el sumatorio de todos los valores creados por las n hebras
        exit (EXIT_SUCCESS);
        
}