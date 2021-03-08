#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

int camisetas[] = {0,0,0,0,0};                          //Iniciamos el vector lleno de 0 por defecto
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      //Mutex

void rellenarVector(int v[], int t){                    //Le pasamos como parametros el vector a rellenar y su tamaño
    for (int i = 0; i<t; i++){
        v[i] = 1 + rand()%100;                          //Rellenamos cada posicion del vector con numeros aleatorios
    }
}

void * compra(){
    int i = 1 + rand()%5;                               //Aleatoriamente seleccionamos el tipo de camiseta a comprar
    int cantidad = 1 + rand()%10;                       //Aleatoriamente seleccionamos la cantidad de camisetas a comprar
    printf("El comprador %ld va a adquirir %d camisetas del tipo %d\n", pthread_self(), cantidad, i);
    
    if (pthread_mutex_lock(&mutex)){                    //Lock del semaforo con comprobacion de error
        printf("Error en bloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }

        camisetas[i-1] = camisetas[i-1] - cantidad;     //Restamos la cantidad vendida del tipo de camiseta correspondiente

    if (pthread_mutex_unlock(&mutex)){                  //Unlock del semaforo con comprobacion de error
        printf("Error en desbloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);                                 //Salimos de la hebra devolviendo NULL para recogerlo en el main
}

void * suministro(){
    int i = 1 + rand()%5;                               //Aleatoriamente seleccionamos el tipo de camiseta a suministrar
    int cantidad = 1 + rand()%10;                       //Aleatoriamente seleccionamos la cantidad de camisetas a suministrar
    printf("El proveedor %ld va a suministrar %d camisetas del tipo %d\n", pthread_self(), cantidad, i);
    
    if (pthread_mutex_lock(&mutex)){                    //Lock del semaforo con comprobacion de error
        printf("Error en bloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }

        camisetas[i-1] = camisetas[i-1] + cantidad;     //Sumamos la cantidad suministrada del tipo de camiseta correspondiente

    if (pthread_mutex_unlock(&mutex)){                  //Unlock del semaforo con comprobacion de error
        printf("Error en desbloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }   
    pthread_exit(NULL);                                 //Salimos de la hebra devolviendo NULL para recogerlo en el main
}

int main(int argc, const char * argv[]){
    if (argc=!3){                                                                       //Comprobamos que el usuario ejecute de forma correcta el programa
        printf("Error, llamar al programa de la siguiente manera: ./ej1 N M \n");
        printf("Donde N = clientes M = proveedores\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));                                                                  //Plantamos la semilla del numero aleatorio

    int numeroClientes = atoi(argv[1]);                                                 //El primer numero sera el numero de clientes (numero de compras que se haran)
    int numeroProveedores = atoi(argv[2]);                                              //El primer numero sera el numero de proveedores (numero de suministros que se haran)
    int modelosCamiseta = atoi(argv[2]);                                                //El enunciado nos indica que el numero de proveedores sera igual a la cantidad de modelos de camisetas

    rellenarVector(camisetas, numeroProveedores);                                       //Rellenamos el vector que declaramos en la zona global

    printf("Stock disponible de cada camiseta antes de abrir la tienda: \n");           //Mostramos con el bucle por pantalla el numero de camisetas de cada tipo antes de aplicar las ventas y los suministros
    for(int i = 0; i<numeroProveedores; i++){
        printf("- Camisetas del tipo %d : %d\n", i+1, camisetas[i]);
    }

    pthread_t threadCliente[numeroClientes];                                            //Vector de hebras. El total de hebras seran el total de clientes
    pthread_t threadProveedor[numeroProveedores];                                       //Vector de hebras. El total de hebras seran el total de proveedores

    printf("-------------------------------------------------------------------\n");
    for(int i = 0; i<numeroClientes; i++){                                              //Creamos las hebras de los clientes
        if(pthread_create(&threadCliente[i], NULL, compra, NULL)){
            printf("Error al crear la hebra. Codigo de error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<numeroProveedores; i++){                                           //Creamos las hebras de los proveedores
        if(pthread_create(&threadProveedor[i], NULL, suministro, NULL)){
            printf("Error al crear la hebra. Codigo de error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<numeroClientes; i++){                                              //Recogemos las hebras de los clientes
        if(pthread_join(threadCliente[i], NULL)){
            printf("Error al recoger la hebra. Codigo de error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i<numeroProveedores; i++){                                           //Recogemos las hebras de los proveedores
        if(pthread_join(threadProveedor[i], NULL)){
            printf("Error al recoger la hebra. Codigo de error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    printf("-------------------------------------------------------------------\n");
    printf("Stock disponible de cada camisetas al cerrar la tienda: \n");               //Mostramos con el bucle por pantalla el numero de camisetas de cada tipo despues de aplicar las ventas y los suministros
    for(int i = 0; i<numeroProveedores; i++){
        printf("- Camisetas del tipo %d : %d\n", i+1, camisetas[i]);
    }
    exit(EXIT_SUCCESS);                                                                 //Salimos del programa
}