
#include<stdio.h>
#include<time.h>
#include <locale.h>


int main(){

	time_t tiempo;
	struct tm * stTm;
	char cadena [80];


	tiempo = time(NULL);

	setlocale(LC_ALL,"");
	
	stTm = localtime(&tiempo);

	strftime(cadena,80,"%A, %d de %B", stTm);

	
	printf("Cadena: %s", cadena);
	
	
	/*FORMATOS PARA USAR CON LA ESTRUCTURA stTm
	%B - nombre del mes completo (January, ...)
	%b - nombre del mes abreviado (Jan, ...)
	%A -  nombre de la semana completo (Sundey, ...)
	%a - nombre de la semana abreviado (Sun, ....)
	%d - día del mes en dos dígitos (01-31)
	%m - el mes en dos dígitos (01-12)
	%D  - fecha en formato %m/%d/%y
	%H - hora en dos dígitos (00-23)
	%M - minutos en dos dígitos
	%S- segundos en dos dígitos
	%Y - nos devuelve el año en cuatro dígitos*/



return 0;	


}
