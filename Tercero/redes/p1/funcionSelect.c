#include<stdio.h>
#include<sys/time.h>
#include<sys/socket.h>

int main(){

	struct timeval timeout;
	fd_set lectura;
	int salida;
	char cadena[60];

	//Inicializar la estructua timeval
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	//Inicializar los conjuntos fd_set
	FD_ZERO(&lectura);
	FD_SET(0,&lectura);
	

	salida = select(1,&lectura,NULL,NULL,&timeout);
	
	if(salida == -1)
	{
		printf("Se ha producido un error en select\n");
	}
	else if(salida == 0)
	{
		printf("Se ha agotado el tiempo\n");

	}
	else{
		
		fgets(cadena,sizeof(cadena),stdin);
		printf("Se ha escrito por pantalla: %s\n",cadena);
	}

		
	
return 0;

}
