#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

/*
 * El servidor envía la fecha o la hora dependiendo de la respuesta recibida por el cliente
 */

int main()
{
    /*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
    int Socket_Servidor;
    struct sockaddr_in Servidor;
    int contador = 0;

    /* -----------------------------------------------------
   		Informaci\ufffdn del Cliente
   	-----------------------------------------------------*/
    struct sockaddr_in Cliente;
    socklen_t Longitud_Cliente;

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
		Se abre el socket Servidor
	---------------------------------------------------*/
    Socket_Servidor = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket_Servidor == -1)
    {
        printf("No se puede abrir socket servidor\n");
        exit(-1);
    }

    /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura servidor, necesaria
		para la llamada a la funcion bind().
	-------------------------------------------------------------------*/
    Servidor.sin_family = AF_INET;
    Servidor.sin_port = htons(2000);
    Servidor.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(Socket_Servidor, (struct sockaddr *)&Servidor, sizeof(Servidor)) == -1)
    {
        close(Socket_Servidor);
        exit(-1);
    }

    /*---------------------------------------------------------------------
		Del cliente s\ufffdlo necesitamos el tama\ufffdo de su estructura, el 
		resto de informaci\ufffdn (familia, puerto, ip), la obtendremos 
		nos la proporcionar\ufffd el propio m\ufffdtodo recvfrom, cuando
		recibamos la llamada de un cliente.
   ----------------------------------------------------------------------*/
    Longitud_Cliente = sizeof(Cliente);

    /*-----------------------------------------------------------------------
		El servidor espera continuamente los mensajes de los clientes
	------------------------------------------------------------------------ */
    while (1)
    {
        /* -----------------------------------------------------------------
			Esperamos la llamada de alg\ufffdn cliente
		-------------------------------------------------------------------*/
        int recibido = recvfrom(Socket_Servidor, &contador, sizeof(contador), 0,
                                (struct sockaddr *)&Cliente, &Longitud_Cliente);

        /* -----------------------------------------------------------------
			Comprobamos si hemos recibido alguna informaci\ufffdn 
		-------------------------------------------------------------------*/
        if (recibido == 'DAY' || recibido == 'TIME' || recibido == 'DAYTIME')
        {
            /*-----------------------------------------------------------------
				Incrementamos el valor que nos ha enviado el cliente 
				------------------------------------------------------------------*/
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

            /*FORMATOS PARA USAR CON LA ESTRUCTURA stTm
                %B - nombre del mes completo (January, ...)
                %b - nombre del mes abreviado (Jan, ...)
                %A -  nombre de la semana completo (Sundey, ...)
                %a - nombre de la semana abreviado (Sun, ....)
                %d - d�a del mes en dos d�gitos (01-31)
                %m - el mes en dos d�gitos (01-12)
                %D  - fecha en formato %m/%d/%y
                %H - hora en dos d�gitos (00-23)
                %M - minutos en dos d�gitos
                %S- segundos en dos d�gitos
                %Y - nos devuelve el a�o en cuatro d�gitos*/

            /* ------------------------------------------------------------------
				Devolvemos el número incrementado al cliente
				--------------------------------------------------------------------*/
            int enviado = sendto(Socket_Servidor, &cadena, sizeof(cadena), 0,
                                 (struct sockaddr *)&Cliente, Longitud_Cliente);
        }
    }

    close(Socket_Servidor);

    return 0;
}