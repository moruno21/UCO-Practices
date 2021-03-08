//Programa que calcula el factorial de dos números pasados por línea de argumentos usando el programa factorial

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char const *argv[]){
    int status;
    if ( argc != 3 ) {
        printf("Error, introduzca dos numeros \n");
    }

    for (int i=0; i<2; i++){
        
        switch (fork()){
        
        case -1:
            printf("Error en la creacion del hijo \n");
        exit(EXIT_FAILURE);

        case 0:
            
            if (i==0){
                execlp("./factorial", "./factorial", argv[1], NULL );
            }

            else{
                execlp("./factorial", "./factorial", argv[2], NULL );


            }
        exit(EXIT_SUCCESS);


        default:
            printf("Esperando a que acaben mis chiquillos \n");
        }

    }
    
    pid_t pidh1, pidh2;
    pidh1 = wait(&status);
    printf("Hijo 1 acabado con codigo de salida %d \n", WEXITSTATUS(status));
    pidh2 = wait(&status);
    printf("Hijo 2 acabado con codigo de salida %d \n", WEXITSTATUS(status));
    
    return 0;



}