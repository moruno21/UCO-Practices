#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include "common.h"

void funcionLog(char *);

// Apuntador al fichero de log. No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fLog = NULL;

//Descriptores de cola
mqd_t mq_server;
mqd_t mq_client;

// Buffers para intercambiar mensajes
char writeBuffer[MAX_SIZE];
char readBuffer[MAX_SIZE];

// Nombres para la cola
char serverQueue[100];
char clientQueue[100];

void sigint(int signal) //Funcion para capturar señales
{
	sprintf(writeBuffer, "Capturada la señal SIGINT con número: %d", signal);
	funcionLog(writeBuffer);
	sprintf(writeBuffer, "exit");
	if (mq_send(mq_server, writeBuffer, MAX_SIZE, 0) != 0)
	{
		perror("Error al enviar el mensaje");
		exit(-1);
	}
	funcionLog(writeBuffer);
	printf("\n");
	// exit(0);
	return;
}

void sigterm(int signal) //Funcion para capturar señales
{
	sprintf(writeBuffer, "Capturada la señal SIGTERM con número: %d", signal);
	funcionLog(writeBuffer);
	sprintf(writeBuffer, "exit");
	if (mq_send(mq_server, writeBuffer, MAX_SIZE, 0) != 0)
	{
		perror("Error al enviar el mensaje");
		exit(-1);
	}
	funcionLog(writeBuffer);
	printf("\n");
	// exit(0);
	return;
}

int main(int argc, char **argv)
{
	if (signal(SIGINT, sigint) == SIG_ERR)
		printf("No puedo asociar la señal SIGINT al manejador!\n");

	if (signal(SIGTERM, sigterm) == SIG_ERR)
		printf("No puedo asociar la señal SIGTERM al manejador!\n");

	// No es necesario crear las colas si se lanza primero el servidor, sino el programa no funciona.

	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER")); // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
	printf("[Cliente]: El nombre de la cola del servidor es: %s\n", serverQueue);

	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER")); // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
	printf("[Cliente]: El nombre de la cola del cliente es: %s\n", clientQueue);

	mq_server = mq_open(serverQueue, O_WRONLY); //Abrimos la de server en escritura
	mq_client = mq_open(clientQueue, O_RDONLY); //Abrimos la de cliente en lectura

	if (mq_server == (mqd_t)-1) //Control de errores
	{
		perror("Error al abrir la cola del servidor");
		exit(-1);
	}

	if (mq_client == (mqd_t)-1) //Control de errores
	{
		perror("Error al abrir la cola del cliente");
		exit(-1);
	}

	printf("[Cliente]: El descriptor de la cola del servidor es: %d\n", (int)mq_server); //Descriptor de la cola de servidor
	printf("[Cliente]: El descriptor de la cola del cliente es: %d\n", (int)mq_client);	 //Descriptor de la cola de cliente

	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
	do
	{
		printf("> ");

		/* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
		It stops when either (n-1) characters are read, the newline character is read,
		or the end-of-file is reached, whichever comes first.
		Automáticamente fgets inserta el fin de cadena '\0'
		*/
		fgets(writeBuffer, MAX_SIZE, stdin);

		if (mq_send(mq_server, writeBuffer, MAX_SIZE, 0) != 0) // Enviar y comprobar si el mensaje se manda
		{
			perror("Error al enviar el mensaje");
			exit(-1);
		}
		funcionLog(writeBuffer);

		ssize_t bytes_read; // Número de bytes leidos

		bytes_read = mq_receive(mq_client, readBuffer, MAX_SIZE, NULL); // Recibir el mensaje

		if (bytes_read < 0) // Comprar que la recepción es correcta (bytes leidos no son negativos)
		{
			perror("Error al recibir el mensaje");
			exit(-1);
		}
		// Cerrar la cadena
		//buffer[bytes_read] = '\0';
		printf("%s\n", readBuffer);

		// Iterar hasta escribir el código de salida
	} while (strncmp(writeBuffer, MSG_STOP, strlen(MSG_STOP)));

	if (mq_close(mq_server) == (mqd_t)-1) // Cerrar la cola del servidor
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	if (mq_close(mq_client) == (mqd_t)-1) // Cerrar la cola del cliente
	{
		perror("Error al cerrar la cola del cliente");
		exit(-1);
	}

	return 0;
}

/* Función auxiliar, escritura de un log.
No se usa en este ejemplo, pero le puede servir para algun
ejercicio resumen */
void funcionLog(char *mensaje)
{
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero, "log-cliente.txt");
	if (fLog == NULL)
	{
		fLog = fopen(nombreFichero, "at");
		if (fLog == NULL)
		{
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm *p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir, fLog);
	if (resultado < 0)
		perror("Error escribiendo en el fichero de log");

	fclose(fLog);
	fLog = NULL;
}