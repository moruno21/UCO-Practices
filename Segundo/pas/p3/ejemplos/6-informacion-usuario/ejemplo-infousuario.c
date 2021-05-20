#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
Consulte el fichero /etc/passwd para ver que significa cada uno de sus campos, como por ejemplo en esta linea:
jfcaballero:x:1000:1000:Juan Carlos Fernández Caballero,,,:/home/jfcaballero:/bin/bash

Haga lo mismo para el fichero /etc/group, identifique cada campo, como por ejemplo:
adm:x:4:syslog,jfcaballero

Ejemplos de ejecución para este programa:
%$> ./a.out
%$> ./a.out jfcaballero
*/

int main(int argc, char *argv[]) {
    // Declaracion de las estructuras que almacenarán la informarción de un usuario y de un grupo
    char *lgn;
    struct passwd *pw;
    struct group *gr;

    // En el caso de que no se ha introducido ningún nombre de usuario,
    // por defecto en lgn almacenara el usuario que ha ejecutado este programa

    // OJO, NO USAR getlogin() porque no funciona en determinados sistemas, depende del
    // terminal y unos ficheros asociados a él, es mejor coger el usuario actual a partir
    // de la variable de entorno USER (getenv("USER")) y pasarselo a getpwnam(). Modifique el programa para ello.
    if (argc < 2) {
        //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
        if ((lgn = getlogin()) == NULL || (pw = getpwnam(lgn)) == NULL) {
            fprintf(stderr, "Fallo al obtener información de usuario.\n");
            exit(1);
        }
    } else //Se indica el nombre de usuario en el primer argumento.
    {
        lgn = argv[1];

        if ((pw = getpwnam(lgn)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
        {
            fprintf(stderr, "Fallo al obtener información de usuario.\n");
            exit(1);
        }
    }

    //Aqui ya se dispone de la estructura que contiene informacion del usuario
    printf("Nombre: %s\n", pw->pw_gecos); //No es lo mismo el nombre de usuario asociado a un login que el propio login
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);

    // Obtenemos la estructura de información del grupo a través del número de grupo al que pertenece el usuario
    gr = getgrgid(pw->pw_gid);

    //Se imprime el campo de la estructura que nos interesa
    printf("Nombre del grupo principal: %s\n", gr->gr_name);

    exit(0);
}
