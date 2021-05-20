/* Cabeceras */
#include <stdio.h>      /* Entrada salida */
#include <stdlib.h>     /* Utilidades generales */
#include <signal.h>     /* Manejo de señales */
#include <unistd.h>

int dividendo=0;

void mi_manejador_sigfpe(int signal)
{
    printf("Capturé la señal DIVISIÓN por cero (%d), divisor establecido a 1\n", signal);
    printf("Division=%d\n", (dividendo/1));
    exit(1);
}

int main()
{
	int divisor=0;

	/*
	SIGFPE Error en coma flotante. Es enviada cuando el hardware detecta un error en coma flotante, 
	como el uso de número en coma flotante con un formato desconocido, errores de overflow o underflow, etc.
	*/
    if (signal(SIGFPE, mi_manejador_sigfpe) == SIG_ERR)
        printf("No puedo asociar la señal SIGFPE al manejador!\n");

    printf("Introduce el dividendo: ");
    scanf("%d", &dividendo);
    
    printf("Introduce el divisor: ");
    scanf("%d", &divisor);
    
    printf("Division=%d\n", (dividendo/divisor));

    exit(0);
}
