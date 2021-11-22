/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculator.h"
#include <time.h>

int
main (int argc, char *argv[])
{


	int primero=0;
	int segundo=0;
	

	printf("Introduzca el primer operando: ");
	scanf("%i",&primero);
	while(abs(primero) > 9){
		printf("Introduzca el primer operando: ");
		scanf("%d",&primero);
	}
	

	printf("Introduzca el segundo operando: ");
	scanf("%i",&segundo);
	while(abs(segundo) > 9){
		printf("Introduzca el segundo operando");
		scanf("%d",&segundo);
	}


	operandos operandos = {primero, segundo};
	int resultado = 0;
	clock_t principio = clock();

	for(int i=0; i<100000; i++){
		resultado = resultado + suma(&operandos);
	}

	clock_t fin = clock();
	double tiempo = (double) (fin-principio) / CLOCKS_PER_SEC;

	printf("El resultado es: %i\n", resultado);
	printf("El tiempo es %f segundos\n", tiempo);

exit (0);
}
