//Programa que crea hijos en forma de dinastía -> Abuelo, padre, hijo...

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int n, child, status;
    printf("Hijos que quiera crear: \n");
    scanf("%d", &n);

    printf("Soy el padre con ID %d \n", getpid());

    for (int i=0; i<n; i++){
        child = fork();
        switch (child){
        
        case -1:
            printf("Error en la creación del proceso hijo \n");
            exit(EXIT_FAILURE);
        
        case 0:
            printf("Soy el hijo numero %d con ID %d del proceso %d \n", i+1, getpid(), getppid());
        break;

        default:
            printf("Esperando a que mi hijo %d termine \n", i+1);
            wait(&status);
            printf("El proceso %d ha finalizado, codigo de salida: %d \n", child, WEXITSTATUS(status));
            exit(EXIT_SUCCESS);

        }

        
    }    
    
}