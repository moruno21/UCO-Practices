#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

/* --------------------------------------------------------------------------------------
 
 Envía un número aleatorio al servidor, quien el devuelve el número incrementado

---------------------------------------------------------------------------------------- */

int main()
{

    /*---------------------------------------------------- 
			Descriptor del socket y buffer para datos 
		-----------------------------------------------------*/
    int Socket_Cliente;
    char datos[100];

    /* -----------------------------------------------------
   		Información del Servidor
   	-----------------------------------------------------*/
    struct sockaddr_in Servidor;
    socklen_t Longitud_Servidor;

    /* -----------------------------------------------------
   		Estructura timeval
   	-----------------------------------------------------*/

    struct timeval timeout;
    fd_set lectura;
    int salida;
    char cadena[60];

    //Inicializar la estructua timeval
    timeout.tv_sec = 5;  //5 segundos
    timeout.tv_usec = 0; //0 milisegundos

    /* -----------------------------------------------------
   		VAriables para la hora y el tiempo
   	-----------------------------------------------------*/

    time_t tiempo;
    struct tm *stTm;
    char cadena[80];

    tiempo = time(NULL);

    setlocale(LC_ALL, "");

    stTm = localtime(&tiempo);

    /* --------------------------------------------------
			Se abre el socket cliente
		---------------------------------------------------*/
    Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket_Cliente == -1)
    {
        printf("No se puede abrir el socket cliente\n");
        exit(-1);
    }

    /*---------------------------------------------------------------------
			Necesitamos una estructura con la información del Servidor
			para poder solicitarle un servicio.
   		----------------------------------------------------------------------*/
    Servidor.sin_family = AF_INET;                     //Familia del servidor
    Servidor.sin_port = htons(2000);                   //Puerto del servidor
    Servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); //Ip del servidor
    Longitud_Servidor = sizeof(Servidor);              //Tamaño del servidor

    /*---------------------------------------------------------------------
			Aquí vamos a realizar un select para comprobar si el servidor 
            esta activo, en caso contrario saldrá del programa.
   		----------------------------------------------------------------------*/

    //Inicializar los conjuntos fd_set
    FD_ZERO(&lectura);   //Initialises the file descriptor lectura to have zero bits for all file descriptors.
    FD_SET(0, &lectura); //Sets the bit for the file descriptor 0 in the file descriptor lectura.

    for (int i = 0; i < 3; i++)
    {
        salida = select(1, &lectura, NULL, NULL, &timeout);
        if (salida <= 0)
            break;
    }
    if (salida == -1)
        printf("Se ha producido un error en select\n");
    else if (salida == 0)
        printf("Se ha agotado el tiempo\n");

    printf("Inserte 'DAY' para obtener el día\n");
    printf("Inserte 'TIME' para obtener la hora\n");
    printf("Inserte 'DAYTIME' para obtener el día y la hora\n");
    scanf("%s", datos);

    /*-----------------------------------------------------------------------
			Se envía mensaje al Servidor
		-----------------------------------------------------------------------*/

    char enviado = sendto(Socket_Cliente, (char *)&datos, sizeof(datos), 0,
                          (struct sockaddr *)&Servidor, Longitud_Servidor);

    /*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
		----------------------------------------------------------------------- */
    char recibido = recvfrom(Socket_Cliente, (char *)&datos, sizeof(datos), 0,
                             (struct sockaddr *)&Servidor, &Longitud_Servidor);

    if (recibido == 'DAY')
    {
        strftime(cadena, 80, "%A, %d de %B de %y", stTm);
        printf("Cadena: %s", cadena);
    }
    if (recibido == 'TIME')
    {
        strftime(cadena, 80, "%H:%M:%S", stTm);
        printf("Cadena: %s", cadena);
    }
    if (recibido == 'DAYTIME')
    {
        strftime(cadena, 80, "%A, %d de %B de %y; %H:%M:%S", stTm);
        printf("Cadena: %s", cadena);
    }

    else
        printf("Error al leer del servidor\n");

    close(Socket_Cliente);
    return 0;
}