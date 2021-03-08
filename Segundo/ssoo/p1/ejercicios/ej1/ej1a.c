//Programa que crea hijos de un solo padre

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int n, status;
    pid_t childpid;
    printf("Hijos que quiera crear: \n");
    scanf("%d", &n);

    printf("Soy el padre con ID %d \n", getpid());

    for (int i=0; i<n; i++){
        
        switch (fork()){
        
        case -1:
            printf("Error en la creación del proceso hijo \n");
            exit(EXIT_FAILURE);
        
        case 0:
            printf("Soy el hijo numero %d con ID %d del proceso %d \n", i+1, getpid(), getppid());
            exit(EXIT_SUCCESS);

        default:
            printf("Esperando a que mi hijo %d termine \n", i+1);
        }


        
    }    
        while ( (childpid=waitpid(-1, &status, WUNTRACED | WCONTINUED)) > 0 )//Si lo hacemos así en vez de con wait podemos saber si el proceso ha sido pausado y poniendo -1 en el primer parametro de waitpid esperamos a cualquier hijo
	{//Este bucle se repetirá mientas haya hijos que esperar cuando no haya mas wait devolverá -1
		
    if (WIFEXITED(status)){//Entrará en el caso de que el hijo haya finaizado correctamente ya que WIFEXITED(status) devolverá true
			printf("Proceso padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)childpid, WEXITSTATUS(status));
		} 

		else if (WIFSIGNALED(status)){//Entrará en el caso de que el proceso haya finalizado debido a una señar externa ya sea de finalizar o matar 
			printf("Proceso padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)childpid, WTERMSIG(status));
		}//La macro WTERMSIG nos dice que señal ha sido la que ha recibido el proceso que ha producido que acabe 

	}

	if (childpid==(pid_t)-1 && errno==ECHILD){//Entra cuando vuelve al while y no hay más hijos que esperar porque en ese caso chilpid valdrá -1 y erno 10 que es el valor que devuelce ECHILD cuando no hay mas procesos hijo
		printf("Proceso padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	}	//strerror devuelve una cadena de caracteres que nos permite identificar el valor de la variable errno

	else{//Solo entra si se ha producido un error con wait 
		printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE); //Acaba el proceso padre con error
	}

  exit(EXIT_SUCCESS); //Como todo ha ido bien el proceso padre acaba exitosamente
    
}