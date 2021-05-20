#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.

int main()
{
    pid_t rf, flag;
    int status;
    
    rf = fork();
    switch (rf)
    {
    	case -1:
        printf ("Proceso Padre, no he podido crear el proceso hijo \n");
        exit(EXIT_FAILURE);
  	  case 0:
        printf ("Soy el Hijo, mi PID es %d y mi PPID es %d \n", getpid(), getppid());
        exit(EXIT_SUCCESS);
  	  default:
        printf ("Soy el Padre, mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
    }

	/*Espera del padre a los hijos*/
	//Pruebe a sustituir wait() por waitpid()
	while ( (flag=wait(&status)) > 0 ) 
	{
		if (WIFEXITED(status)) {
			printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
		} 
		else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
			printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
		} 		
	}
	if (flag==(pid_t)-1 && errno==ECHILD)
	{
		printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	}
	else
	{
		printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		exit(EXIT_FAILURE);
	}		 
}
