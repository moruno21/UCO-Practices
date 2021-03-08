//Ejercicio que manda una señal SIGUSR1 Y SIGKILL a un id que introduzcamos por línea de argumentos
//Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned and errno set to indicate the error.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int main( int argc, char const *argv[]){
    if (argc!=2){
        printf("Error introduzca un PID válido \n");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = atoi(argv[1]);
    if (pid<0){
        printf("No introduzcas un PID negativo, sinverguenza \n");
    }

    if (kill(pid, SIGUSR1)){//Enviamos señal, si devuelve algo distinto a 0 entramos en ek if y nos da el error
        printf("Error al enviar SIGUSR1: %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    sleep(1);
    if (kill(pid, SIGKILL)){//Enviamos señal, si devuelve algo distinto a 0 entramos en el if y nos da el error
        printf("Error al enviar SIGKILL: %s \n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
return EXIT_SUCCESS;
}