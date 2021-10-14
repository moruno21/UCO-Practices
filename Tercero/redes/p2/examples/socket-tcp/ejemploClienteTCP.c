#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/* El cliente manda cadena de textos al servidor hasta que manda la cadena FIN */

int main()
{

	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd;						 //Descriptor de socket
	struct sockaddr_in sockname; //Estructura básica con 4 parámetros
	char buffer[100];			 //Tamaño de la cadena que introduciremos por teclado
	socklen_t len_sockname;		 //Longitud del socket

	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
	sd = socket(AF_INET, SOCK_STREAM, 0); //Abrimos el socket, que nos devuelve su descriptor
	if (sd == -1) //Comprobacion de errores
	{
		perror("No se puede abrir el socket cliente\n");
		exit(1);
	}

	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	sockname.sin_family = AF_INET; //Familia del socket
	sockname.sin_port = htons(2000); //Converts 2000 from host byte order to network byte order. 
	sockname.sin_addr.s_addr = inet_addr("127.0.0.1"); //Converts the IP to an interger value suitable for use as an internet address

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	len_sockname = sizeof(sockname); //Guardamos la longitud de la estructura

	//Hacemos la conexion con el descriptor de socket, la estructura sockname (requiere un casting) y el tamaño de dicha estructura 
	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
	{
		perror("Error de conexión");
		exit(1);
	}

	/* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
	do
	{
		puts("Teclee el mensaje a transmitir");
		gets(buffer);

		if (send(sd, buffer, 100, 0) == -1)
			perror("Error enviando datos");

	} while (strcmp(buffer, "FIN") != 0);

	close(sd); //Cerramos el descriptor de socket
	return 0;
}
