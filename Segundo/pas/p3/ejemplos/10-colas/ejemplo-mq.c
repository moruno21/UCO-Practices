#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h> //Control de errores
#include <string.h> //Para la funcion strerror()

#define MAX_SIZE    5
#define QUEUE_NAME  "/una_cola"

int main()
{
	// Descriptor de la cola
	mqd_t mq;
	// Buffer para la lectura/escritura
	char buffer[MAX_SIZE];
	// Atributos de la cola
	struct mq_attr attr;
    // Almacena el nombre de la cola
    char queue_name[100];
	// Resultado de las operaciones
	int resultado;
	// Para realizar el fork
    pid_t rf, flag;
    int status;
	// Numero aleatorio a generar
	int numeroAleatorio;
	// Inicializar los atributos de la cola.
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje. Tener en cuenta que debe incluir el '/0'
    // Nombre para la cola. Al concatenar el login, sera unica en un sistema compartido.
    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER"));

	// Realizar el fork
	rf = fork();
	switch (rf)
	{
		// Error
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);

		case 0: // Hijo. El hijo solo se encargará de escribir.

			/* Apertura de la cola
			   O_CREAT: si no existe, se crea
			   O_RDWR: lectura/escritura
			   O_RDONLY: solo lectura
			   O_WRONLY: solo escritura
			   0644: permisos rw-r--r--
			         permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
			   attr: estructura con atributos para la cola  */
			mq = mq_open(queue_name, O_CREAT | O_WRONLY, 0644, &attr);
            printf ("[HIJO]: El nombre de la cola es: %s\n", queue_name);
            printf ("[HIJO]: El descriptor de la cola es: %d\n", (int) mq);

			if(mq==-1)
			{
				perror("[HIJO]: Error en la apertura de la cola");
				exit(-1);
			}
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

			/* Rellenamos el buffer que vamos a enviar
			   Semilla de los números aleatorios, establecida a la hora actual*/
			srand(time(NULL));
			// Número aleatorio entre 0 y 4999
			numeroAleatorio = rand()%5000;
			sprintf(buffer,"%d",numeroAleatorio); // La funcion sprintf escribe en una cadena el valor indicado y añade el '/0'.
			printf("[HIJO]: Generado el mensaje \"%s\"\n", buffer);

			// Mandamos el mensaje
			printf("[HIJO]: Enviando mensaje...\n");
			resultado = mq_send(mq, buffer, MAX_SIZE, 0);
			if(resultado == -1)
			{
				perror("[HIJO]: Error al enviar mensaje");
				exit(-1);
			}

			printf("[HIJO]: Mensaje enviado!\n");
			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[HIJO]: Error cerrando la cola");
				exit(-1);
			}
            printf("[HIJO]: Cola cerrada.\n");
			break; //Saldría del switch()

		default: // Padre. El padre solo se encargará de leer

			/* Apertura de la cola */
			mq = mq_open(queue_name, O_CREAT | O_RDONLY, 0644, &attr);
            printf ("[PADRE]: El nombre de la cola es: %s\n", queue_name);
            printf ("[PADRE]: El descriptor de la cola es:%d\n", (int) mq);

			if(mq==-1)
			{
				perror("[PADRE]: Error en la apertura de la cola");
				exit(-1);
			}

			printf ("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			printf ("[PADRE]: Recibiendo mensaje (espera bloqueante)...\n");

			// Recibimos un mensaje a través de la cola
			resultado = mq_receive(mq, buffer, MAX_SIZE, NULL);
			if(resultado <= 0)
			{
				perror("[PADRE]: Error al recibir el mensaje");
				exit(-1);
			}

			// Imprimimos el mensaje recibido
			printf("[PADRE]: El mensaje recibido es \"%s\"\n", buffer);

			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[PADRE]: Error cerrando la cola");
				exit(-1);
			}
			printf("[PADRE]: Cola cerrada.\n");

			// Eliminar la cola
			if(mq_unlink(queue_name) == -1)
			{
				perror("[PADRE]: Error eliminando la cola");
				exit(-1);
			}

    	/*Espera del padre a los hijos*/
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
	exit(0);
}
