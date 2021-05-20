#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ejecución:  %$>./a.out

int main(void) {
    char *value;

    //Si el valor devuelto en value es "ES" imprime Español, sino imprime INGLES.
    value = getenv("LANG");

    if (strstr(value, "ES")) {
        printf("\nLa carpeta del usuario/a es: %s\n", getenv("HOME"));
    } else {
        printf("\nUser's home folder is: %s\n", getenv("HOME"));
    }
    exit(0);
}
