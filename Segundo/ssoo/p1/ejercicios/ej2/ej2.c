//Comprobar el estado de los procesos en terminal con el comando ps -a
//Programa que muestra como un proceso zombie

#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int status;
    pid_t child;
    printf("Soy el padre \n");
    child = fork();
    if (child==-1){
        printf("Error en la creación del hijo \n");
        exit(EXIT_FAILURE);
    }

    if (child==0){
        printf("Soy el proceso hijo con ID %d \n", getpid());
        exit(EXIT_SUCCESS);
    }

    else{
        printf("Procedo a dormir 20 segundos y después me piro \n");
        sleep(20);
        wait(&status); // Con el wait hacemos que después del primer sleep, el padre espere al hijo y ya no queda más zombie
        printf("Hijo finalizado. Código de salida %d \n", WEXITSTATUS(status));
        sleep(20);
        exit(EXIT_SUCCESS);


    }
}

