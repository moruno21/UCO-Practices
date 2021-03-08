//ej3.c
//Este ejercicio creara un vector de 10 elementos relleno con numeros aleatorios entre 1 y 9, y usando hebras se sumaran sus valores
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

typedef struct {        //Estructura vector que pasaremos a las funciones que manejan los hilos 
  int *vector;          //Vector
  int hebras;           //Hebras
  int i;                //Iterador
} Vector;


void rellenaVector(int *vector){                //Rellenamos el vector de numeros aleatorios del 1 al 9
  srand(time(NULL));                                    
	for (int i = 0; i < 10; ++i){
		vector[i] = ((rand()%9)+1);
	}
}

void imprimeVector (int *vector){               //Imprimimos los elementos del vector
	printf("El vector es:\n");
	printf("| ");
	for (int i = 0; i < 10; ++i){
		printf("%d | ",vector[i]);
	}
	printf("\n");

}


void * sumaVector (void* d){                    //Esta será la función que ejecuten las hebras.
    
    int *suma = malloc(sizeof(int));            //Reservamos memoria para un puntero de tipo int
    *suma = 0;                                  //Como lo vamos a usar de sumador lo ponemos a 0
    
    Vector *v;                                  //Declaramos una estructura de tipo vector              
    v = (Vector*) d;                            //Hacemos casting de void a vector
    

    //AÑADIR SEMAFOROS DENTRO DEL IF Y DEL ELSE PARA QUE EL FUNCIONAMIENTO SEA EL CORRECTO

    if(v->hebras == 2){                         //SI EL USUARIO QUIERE HACER 2 HEBRAS, SOLO ENTRAREMOS EN ESTE IF EN LAS 2 HEBRAS QUE LLAMAMOS
        //Poner un entrar critica

        int j=v->i;
        for(j; j<(v->i)+5; j++){                //SI EL USUARIO QUIERE HACER 2 HEBRAS, TENDREMOS QUE HACER EL PROCESO DESDE LA POSICION VECTOR[0] A VECTOR[4] PARA EMPEZAR
            printf("Hola, soy la hebra %lu\n", pthread_self());
            *suma = *suma + v->vector[j];
            sleep(1);
        }

        v->i = v->i + 5;
        //Poner un salir critica
        pthread_exit((void**)suma);             //Devolvemos la suma 
    }

    else{                                       //SI EL USUARIO QUIERE HACER 5 HEBRAS, SOLO ENTRAREMOS EN ESTE ELSE EN LAS 5 HEBRAS QUE LLAMAMOS
        //Poner un entrar critica
        
        printf("Hola, soy la hebra %lu\n", pthread_self());
        int j=v->i;
        for(j; j<(v->i)+2; j++){                //SI EL USUARIO QUIERE HACER 5 HEBRAS, TENDREMOS QUE HACER EL PROCESO DESDE LA POSICION VECTOR[0] A VECTOR[1] PARA EMPEZAR
            printf("Hola, soy la hebra %lu\n", pthread_self());
            *suma = *suma + v->vector[j];
            sleep(1);
        }

        v->i = v->i + 2;
        //Poner un salir critica
        pthread_exit((void**)suma);             //Devolvemos la suma 
    }
}


int main(int argc, char const *argv[]){
  
    Vector *v = malloc(sizeof(Vector));                 //Reservamos memoria para una estructura de tipo Vector
    
    if (argc != 2){                                     //Comprobamos que se haya llamado al programa de forma adecuada introduciendo 2 argumentos. Hacemos este if primero para evitar un segmentation fault en la linea 79
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");
        exit(EXIT_FAILURE);
    }

    v->hebras = atoi(argv[1]);                          //Guardamos en v->hebras el numero de hebras que queremos hacer
    v->i = 0;                                           //Ponemos el iterador a 0 para luego en la funcion sumaVector comenzar desde la posicion 0 del vector 

    if (v->hebras != 2 && v->hebras != 5){              //Comprobamos que se haya llamado al programa de forma adecuada introduciendo un 2 o un 5
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");
        exit(EXIT_FAILURE);
    }
    
    v->vector = (int *)malloc (10*sizeof(int));         //Reservamos memoria para el vector v->vector
    rellenaVector(v->vector);                           //Rellenamos el vector con numeros aleatorios del 1 al 9
    imprimeVector(v->vector);                           //Imprimimos el vector para comprobar luego el resultado

    pthread_t thread[v->hebras];                        //Creamos un vector para almacenar los identificadores de los hilos, que seran 2 o 5 segun haya indicado el usuario
    int *sumaLinea, suma = 0;                           //sumaLinea es el puntero que recibirá los valores devueltos por los hilos, suma almacenará la suma de los 10 valores del vector
    
    printf("Se pasaran a crear %d hebras para sumar los valores del vector\n", v->hebras);

    for (int i = 0; i < v->hebras; i++){                //Crearemos tantos hilos como haya indicado el usuario por linea de argumentos
        
        if(pthread_create(&(thread[i]), NULL, (void*) sumaVector, (void*) v)){
            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < v->hebras; i++){                //Crearemos tantos hilos como haya indicado el usuario por linea de argumentos
        
        if(pthread_join(thread[i], (void**) &sumaLinea)){
            printf("Error al esperar la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        } 

        suma = suma + *sumaLinea;                       //En cada iteración del bucle sumamos el valor devuelto por la hebra recogida a la suma total de valores
    }

    printf("La suma de los numeros de todos los valores es: %d\n", suma);
    exit(EXIT_SUCCESS);
}     