#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.

int main()
{
    pid_t rf, flag;
    int status;

    char *args[] = {"/bin/ls", "-t", "-l", (char *) 0 };  

    switch(rf=fork())
    {
		 case -1:
     		  printf ("Proceso Padre, no he podido crear el proceso hijo \n");
  	   	  exit(EXIT_FAILURE);
		 case 0 : // código que ejecuta el hijo
		     printf("Hijo %d ejecutando comando ls...\n",getpid()); 
		     execv("/bin/ls", args); //Reemplazo total del hijo por el proceso "ls"
		
		 //default: El padre no hace nada, directamente ya va a esperar a los hijos.
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
