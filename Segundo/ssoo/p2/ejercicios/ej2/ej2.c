//ej2.c
//Este programa cuenta cuantas lineas tienen una serie de ficheros, indicando al final el numero total de lineas
//Como funciona la apertura del fichero y los castings de la funcion cuentaLineas

#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>


void * cuentaLineas (void * argv){

    printf("Hola, esta es la hebra %lu \n", pthread_self());
    
    int *numLineas=malloc(sizeof(int));     //Reservamos memoria para que no se pierda tras acabar la hebra
    *numLineas=0;                           //El numero de lineas antes de comenzar es 0

    char const *fname;                      //Creamos un puntero para deshacer en la siguiente linea el casting a void
    fname=(char *) argv;                    //Deshacemos el casting

    char aux [256];                         //Cadena auxiliar
    
    FILE* f=fopen(fname, "r");              //Creamos puntero para abrir el fichero en modo r (read). EL nombre del fichero esta en fname
    
    if (f==NULL){                           //Si el fichero no se ha abierto correctamente, nos saltara el error

        printf("Error al abrir el archivo. Codigo de error: %d\n", errno);
        pthread_exit(NULL);                 //No ponemos exit(EXIT_FAILURE) porque si la usamos, en vez de finalizar la hebra, finalizaria el proceso (el programa)
    }

    while (fgets(aux, 256, f)!=NULL){       //Cada vez que entremos en el bucle aumentara el numero de lineas
        ++*numLineas;                       //Aumentamos el numero de lineas que tiene el fichero
    }

    fclose(f);                              //Cerramos el fichero

    pthread_exit((void *) numLineas);       //Salimos de la hebra devolviendo el numero de lineas del fichero
}

int main(int argc, const char * argv[]){
    
    if (argc < 2){
        printf("Error debe llamar al programa de la siguiente forma: ./ej2 nombrefichero1, nombrefichero2, ..., nombreficheron\n");
        exit(EXIT_FAILURE);
    }

    int numArchivos = (argc-1);             //Cantidad de ficheros que deberemos tratar
    pthread_t thread[numArchivos];          //Declaramos un vector para almacenar los identificadores de las hebras

    int sumaLineas=0;                       //Suma de las lineas de todos los ficheros
    int *sumaFichero;                       //Suma de las lineas de 1 fichero. Puntero que recibira el valor devuelto por la hebra

    //Si no hacemos 2 for, la funcion pthread_create nos devolvera que todas las hebras tienen el mismo identificador

    for (int i=0; i<numArchivos; i++){

        if (pthread_create(&(thread[i]), NULL, (void *) cuentaLineas, (void*) argv[i+1])){      //No tenemos que poner & ya que argv es un puntero 
            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("Creacion de la hebra %d\n", i+1);            
    }

    for (int i=0; i<numArchivos; i++){

        if (pthread_join(thread[i], (void **) &sumaFichero)){                                   //Si la espera de la hebra nos devuelve algo distinto a 0, habra ocurrido un error
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("Hebra %d recogida\n", i+1);

        sumaLineas=sumaLineas+*sumaFichero;                                                     //Cada vez que acabemos con un fichero, sumamos sus lineas al total de lineas                
    }


    printf("Sumatorio de todas las lineas de todos los ficheros = %d \n", sumaLineas);
    exit(EXIT_SUCCESS);                                                                         //Finalizamos el programa
}