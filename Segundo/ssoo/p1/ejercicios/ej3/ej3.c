//Ejemplo de invocación: ./miPrograma gnome-calculator gedit fichero1.txt fichero2.txt ficheroN.txt

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    int status;


    printf("Hola soy %d y voy a crear dos hijos. El primero abrirá la calculadora y el segundo el editor de textos \n", getpid());
    for(int i=0; i<2; i++){

        switch(fork()){
            case -1:
                printf("Error en la creacion del hijo \n");
            exit(EXIT_FAILURE);

            case 0:
                printf("Hijo %d con ID %d creado con exito \n", i+1, getpid());

                if(i==0){
                    execlp(argv[1], argv[1], NULL);
                }

                else{
                    execlp(argv[2], argv[2], NULL);
                    
                }
                exit(EXIT_SUCCESS);

            default:
                printf("Esperando a que acabe mi chiquillo numero %d \n", i+1);

        }
    }
    
    //Si queremos guardar el id de los procesos hijos, guardamos lo que nos devuelva wait(&status) en variables
    pid_t pidh1, pidh2;

    pidh1 = wait(&status);
    printf("Ya ha acabado mi hijo %d con el codigo de salida: %d\n", pidh1, WEXITSTATUS(status));
    
    pidh2 = wait(&status);
    printf("Ya ha acabado mi hijo %d con el codigo de salida: %d\n", pidh2, WEXITSTATUS(status));
    

    return 0;
}




