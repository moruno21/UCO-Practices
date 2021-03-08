//Programa que comprueba que un hijo no puede modificar una variable global

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int global = 0;

int main(){
    int status;
    
    printf("Soy el padre con ID %d \n", getpid());
    printf("De inicio la variable global vale %d \n", global);

    
        switch (fork()){
        
        case -1:
            printf("Error en la creación del proceso hijo \n");
            exit(EXIT_FAILURE);
        
        case 0:
            printf("Soy el hijo %d del proceso %d \n", getpid(), getppid());
            printf("Voy a intentar sumar uno a la variable global \n");
            global++;
            exit(EXIT_SUCCESS);

        default:
            printf("Esperando a que mi hijo termine \n");
            wait(&status);
            printf("Tras la ejecución de mi hijo, la variable local vale %d \n", global);
            printf("Mi hijo ha finalizado sin poder sumar el muy inútil, codigo de salida: %d \n", WEXITSTATUS(status));


        }

}