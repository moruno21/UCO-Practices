/*
Utilizando el comando kill, prueba a mandar señales a este programa. 
Ejecuta el programa en el background ($ ./ejemplo-signal &), o simplemente dejalo ejecutando en un
terminal y abre otro para el envio de señales.
   
Luego manda señales al proceso, por ejemplo:
kill -SIGHUP pid
kill -SIGINT pid
kill -SIGKILL pid
kill -SIGTERM pid

El pid del último proceso ejecutado en backgroud se puede obtener en bash con $! o ps.
Si lo has dejado ejecutando en un terminal abre el "Monitor de Sistema" y busca su PID.

Prueba a mandar la señal por defecto: 
kill pid
¿Con cuál de las señales mencionadas anteriormente se corresponde la señal por defecto?

Comente todas las declaraciones signal() del main() para el tratamiento de señales
y mande todas las señales anteriores para ver su comportamiento por defecto.

Enteros asociados a las macros de señales:
1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL
5) SIGTRAP      6) SIGABRT      7) SIGBUS       8) SIGFPE
9) SIGKILL     10) SIGUSR1     11) SIGSEGV     12) SIGUSR2
13) SIGPIPE     14) SIGALRM     15) SIGTERM     17) SIGCHLD
18) SIGCONT     19) SIGSTOP     20) SIGTSTP     21) SIGTTIN
22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO
30) SIGPWR      31) SIGSYS      ....

*/

#include <stdio.h>      /* Entrada salida */
#include <stdlib.h>     /* Utilidades generales */
#include <signal.h>     /* Manejo de señales */
#include <unistd.h>


/* Este será nuestro manejador (personalizado) de señales SIGINT.
   SIGINT se genera cuando el usuario pulsa Ctrl-C.
   El comportamiento por defecto de un programa al pulsar Ctrl-C es salir.
   Con nuestro nuevo manejador, no saldrá. 
*/
void mi_manejador_sigint(int signal)
{
    printf("Capturé la señal SIGINT y no salgo!\n");
    return;
}


/* Nuestro manejador para SIGHUP */
void mi_manejador_sighup(int signal)
{
    printf("Capturé la señal SIGHUP y no salgo!\n");
    return;
}

/* Nuestro manejador para SIGTERM */
void mi_manejador_sigterm(int signal)
{
    int i;
    printf("Capturé la señal SIGTERM y voy a salir de manera ordenada\n");
    for(i=0; i<3; i++)
    {
        printf("Hasta luego... cerrando ficheros...\n");
        sleep(1);
    }
    exit(0);
}

/* Nuestro manejador para SIGKILL */
/* ¿Podemos asociar SIGKILL? */
void mi_manejador_sigkill(int signal)
{
    printf("Capturé la señal SIGKILL y no salgo!\n");
    return;
}


int main()
{
	/* Utilizar la función signal() para asociar nuestras funciones a las señales SIGINT, SIGHUP y SIGTERM */
	 
	/* Si la solicitud de tratamiento de senial se puede llevar a cabo, la funcion signal() devolverá 
	el nombre de la función (* void) que la tratará, en caso contrario se devuelve el valor de la macro
	SIG_ERR y se pone errno a un valor positivo*/ 
	  
    if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGHUP, mi_manejador_sighup) == SIG_ERR)
        printf("No puedo asociar la señal SIGHUP al manejador!\n");
    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

    /* ¿Podemos asociar SIGKILL? */
    if (signal(SIGKILL, mi_manejador_sigkill) == SIG_ERR)
        printf("No puedo asociar la señal SIGKILL al manejador!\n");

	 for(;;)
		//No hago nada,solo quedo a la espera de señales
		pause();

    /* exit */
    exit(0);  //¿Llegaremos aquí?
} 
