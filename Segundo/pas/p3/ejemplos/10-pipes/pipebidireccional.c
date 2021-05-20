#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror
#include <time.h> //Para la semilla del generador de aleatorios

int main() 
{
pid_t flag;
int status, status_1, status_2, num, num2;
int fildes_1[2], fildes_2[2];
const int BSIZE = 100;
char buf[BSIZE], mensaje[10];
ssize_t nbytes;


status_1 = pipe(fildes_1);
status_2 = pipe(fildes_2);

if (status_1 == -1 ) 
{
	perror("Error en pipe 1"); 
	exit(EXIT_FAILURE);
}
else if (status_2 == -1 ) 
{
	perror("Error en pipe 2"); 
	exit(EXIT_FAILURE);
}

switch (fork()) 
{
	case -1: // Ocurrió un error al hacer fork()
		perror("No se ha podido crear el proceso hijo...");
		exit(EXIT_FAILURE);

	case 0: 
		if (close(fildes_1[1]) == -1) // En esta tubería solo va a leer
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		if (close(fildes_2[0]) == -1) // En esta tubería solo va a escribir
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
	
		// Leer usando READ
		nbytes = read(fildes_1[0], buf, BSIZE);
		if (nbytes == -1)
		{
			perror("Error en read");
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
			printf("[HIJO]: Detecto que mi padre ha cerrado la tuberia 1...\n"); 
		else
		{
			printf("[HIJO]: Leido %s de la tuberia 1.\n", buf);
			int cont = 0;
			char * token;
			char * token_2;
			token = strtok(buf, ";"); //Leo el primer número
			token_2 = strtok(NULL,";"); //Leo el segundo número

			for(int d=1; d <= atoi(token);d++)
			{
    			if(atoi(token)%d==0)
        			cont++;
    		}
    		if(cont==2) //El primer numero es primo
    		{ 
    			cont = 0;
    			for(int d=1; d <= atoi(token_2);d++) //Calculamos que el segundo número sea primo.
    			{
    				if(atoi(token_2)%d==0)
        				cont++;
    			}
    			if(cont==2) //El segundo numero es primo 
    			{ 
    				if(atoi(token_2) - atoi(token) == 2	) //Son primos gemelos.
    					sprintf(mensaje, "gemelos");
    				else //Ambos son primos, pero no gemelos
    					sprintf(mensaje, "primos");
    			}
    			else //El segundo numero no es primo
    				sprintf(mensaje, "no-primos");
    		}
    		else //El primer numero no es primo
    			sprintf(mensaje, "no-primos");
		}
		
		if (close(fildes_1[0]) == -1) //Se termina de leer -> Cerramos filfes[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[HIJO]: Tuberia 1 cerrada.\n"); 


		if ( write(fildes_2[1], mensaje, 10) == -1)
		{
			perror("Error en write"); 
			exit(EXIT_FAILURE);
		}
		printf("[HIJO]: He escrito en la tuberia 2.\n");


		if (close(fildes_2[1]) == -1) //Se termina de leer -> Cerramos filfes[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[HIJO]: Tuberia 2 cerrada.\n"); 

		exit(EXIT_SUCCESS);

	
	default:
		
		if (close(fildes_1[0]) == -1) // No se necesita leer de la tubería 1
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}

		if (close(fildes_2[1]) == -1) // No se necesita escribir en la tubería 2
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}

		printf("[PADRE]: Inserte dos números enteros para determinar si son primos gemelos, primos o alguno de los dos no es primo.\n");
		printf("[PADRE]: ");
		scanf("%d", &num);
		printf("[PADRE]: ");
		scanf("%d", &num2);
		sprintf(buf, "%d;%d", num, num2);

		// Escribimos datos en la tubería
		if ( write(fildes_1[1], buf, 10) == -1)
		{
			perror("Error en write"); 
			exit(EXIT_FAILURE);
		}
		printf("[PADRE]: He escrito los dos números en la tuberia 1.\n");
	
		// El hijo verá FEOF (por hacer close)
		if (close(fildes_1[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[PADRE]: Tuberia 1 cerrada.\n"); 


		nbytes = read(fildes_2[0], mensaje, 10);
		if (nbytes == -1)
		{
			perror("Error en read");
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
			printf("[PADRE]: Detecto que mi hijo ha cerrado la tuberia 2...\n"); 
		else
			printf("[PADRE]: Leido %s de la tuberia 2.\n", mensaje);
		

		if (close(fildes_2[0]) == -1) //Se termina de leer -> Cerramos filfes[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[PADRE]: Tuberia 2 cerrada.\n"); 


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
		
		exit(EXIT_SUCCESS);	
	}//switch		 
}
