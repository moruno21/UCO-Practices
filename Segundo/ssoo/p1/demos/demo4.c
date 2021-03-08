#include <stdio.h>

extern char **environ;

int main(int argc, char **argv) //Equivalente a (int argc, char *argv[]) 
{
    int i;
    
    printf("Lista de variables de entorno del proceso %s:\n",argv[0]);
    
    for (i=0; environ[i]!= NULL; i++) 
        printf("environ[%d] = %s\n", i, environ[i]);
}
