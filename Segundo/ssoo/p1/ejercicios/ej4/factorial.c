//Programa que calcula el factorial de un numero pasandolo por línea de argumentos

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main( int argc, char const *argv[]){
    
    int fact = 1;
    int n = atoi(argv[1]);

    if (argc!=2){
        printf("Error, introduzca un número para hallar su factorial \n");
    }

    else{

    for (int i=1; i<=n; i++ ){
        sleep(1); //Se espera un segundo en cada iteración
        fact = fact * i;
        printf("%d \n", fact); //Se muestra cada iteración
        
    }
    sleep(1);
    printf("El factorial de %d es %d \n", n, fact);
    return 0;

        
    }

}