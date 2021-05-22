#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

void printUser(struct passwd *pw)
{
    printf("\nUsuario:\n");
    printf("-----------------------------------------\n");
    printf("Nombre: %s\n", strtok(pw->pw_gecos, ",")); //Evita que nos salga Antonio Moruno Gracia,,,
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);
}

void printGroup(struct group *gr)
{
    printf("\nGrupo:\n");
    printf("-----------------------------------------\n");
    printf("Nombre del grupo principal: %s\n", gr->gr_name);
    printf("GID: %d\n", gr->gr_gid);
    printf("Miembros secundarios: %s\n", *gr->gr_mem);
}

void printHelp()
{
    printf("Uso del programa: ejercicio1 [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help Imprimir esta ayuda:\n");
    printf("-u, --user (<nombre>|<uid>) Información sobre el usuario\n");
    printf("-a, --active Información sobre el usuario activo actual\n");
    printf("-m, --maingroup Además de info de usuario, imprimir la info de su grupo principal\n");
    printf("-g, --group (<nombre>|<gid>) Información sobre el grupo\n");
    printf("-s, --allgroups Muestra info de todos los grupos del sistema\n");
}

int main(int argc, char **argv)
{
    int c;      //Variable donde guardamos las opciones que se hayan introducido
    opterr = 0; //Para evitar error en caso de que getopt no reconozca el caracter c

    // Declaracion de las estructuras que almacenarán la informarción de un usuario y de un grupo
    char *lgn;
    int uid;
    char *gname;
    int gid;
    char *name;
    struct passwd *pw;
    struct group *gr;

    // Estructura a utilizar por getoptlong
    static struct option long_options[] = {
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    //Estas variables servirán para almacenar el resultado de procesar la línea de comandos
    char *uvalue = NULL; //Valor del argumento de user
    char *gvalue = NULL; //Valor del argumento de group
    bool aflag = false;  //True si insertamos la opcion a
    bool mflag = false;  //True si insertamos la opcion m
    bool sflag = false;  //True si insertamos la opcion s
    bool hflag = false;  //True si insertamos la opcion h

    while ((c = getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1)
    {
        switch (c)
        {

        case 'u':
            uvalue = optarg; //En optarg quedo guardado el parametro obligatorio que recibio u
            break;

        case 'g':
            gvalue = optarg; //En optarg quedo guardado el parametro obligatorio que recibio g
            break;

        case 'a':
            aflag = true;
            break;

        case 'm':
            mflag = true;
            break;

        case 's':
            sflag = true;
            break;

        case 'h':
            hflag = true;
            break;
        }
    }

    if (argc == 1)
    {
        if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL) //Usar getenv en vez de getlogin()
        {
            fprintf(stderr, "Fallo al obtener información de usuario.\n");
            exit(-1);
        }

        if ((gr = getgrgid(pw->pw_gid)) == NULL)
        {
            fprintf(stderr, "Fallo al obtener información de grupo.\n");
            exit(-1);
        }

        printUser(pw);
        printGroup(gr);
    }

    else
    {
        if (hflag) //Si hemos introducido el comando h, mostrar la guia de help
        {
            printHelp();

            exit(0);
        }

        else if ((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)) //Opcion en la que el usuario introduce la u -> mostrar usuario
        {
            if (isdigit(*uvalue)) //Caso en el que introduce el uid
            {
                uid = atoi(uvalue);

                if ((pw = getpwuid(uid)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario. Probablemente el usuario que ha introducido no exista\n");
                    exit(-1);
                }
            }

            else //Caso en el que introduce el nombre de login
            {
                lgn = uvalue;

                if ((pw = getpwnam(lgn)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario. Probablemente el usuario que ha introducido no exista\n");
                    exit(-1);
                }
            }

            printUser(pw);

            exit(0);
        }

        else if ((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (mflag) && (!sflag) && (!hflag)) //Opcion en la que el usuario introduce el usuario y la m -> maingroup
        {
            if (isdigit(*uvalue)) //Caso en el que el usuario introduce el uid
            {
                uid = atoi(uvalue);

                if ((pw = getpwuid(uid)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario. Probablemente el usuario que ha introducido no exista\n");
                    exit(-1);
                }
            }

            else //Caso en el que el usuario introduce el nombre de login
            {
                lgn = uvalue;

                if ((pw = getpwnam(lgn)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario. Probablemente el usuario que ha introducido no exista\n");
                    exit(-1);
                }
            }

            printUser(pw); //Imprimimos la informacion de usuario

            //Despues de imprimir el usuario, vamos a imprimir el maingroup

            if ((gr = getgrgid(pw->pw_gid)) == NULL)
            {
                fprintf(stderr, "Fallo al obtener información de grupo. Probablemente el grupo que ha introducido no exista\n");
                exit(-1);
            }

            printGroup(gr); //Imprimimos la informacion de grupo

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (aflag) && (!mflag) && (!sflag) && (!hflag)) //Caso en el que el usuario introduce a -> active (mostrar usuario activo)
        {
            if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL)
            {
                fprintf(stderr, "Fallo al obtener información de usuario.\n");
                exit(-1);
            }

            printUser(pw); //Imprimimos la informacion de usuario

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (aflag) && (mflag) && (!sflag) && (!hflag)) //Caso en el que introduce m y a -> maingroup y active
        {
            if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL)
            {
                fprintf(stderr, "Fallo al obtener información de usuario.\n");
                exit(-1);
            }

            printUser(pw); //Imprimimos usuario

            if ((gr = getgrgid(pw->pw_gid)) == NULL)
            {
                fprintf(stderr, "Fallo al obtener información de grupo.\n");
                exit(-1);
            }

            printGroup(gr); //Imprimimos grupo

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue != NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)) //Caso en el que introduce g -> grupo
        {
            if (isdigit(*gvalue)) //Caso en el que introduce el gid
            {
                gid = atoi(gvalue);

                if ((gr = getgrgid(gid)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }

            else //Caso en el que introduce el nombre de grupo
            {
                gname = gvalue;

                if ((gr = getgrnam(gname)) == NULL) //DEVUELVE LA ESTRUCTURA TRAS RECIBIR lgn COMO PARÁMETRO
                {
                    fprintf(stderr, "Fallo al obtener información de usuario.\n");
                    exit(-1);
                }
            }

            printGroup(gr);

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (sflag) && (!hflag)) //Caso en el que introduce s -> allgroups
        {
            int num;
            FILE *f;
            //Abriremos el fichero donde estan los grupos y lo leeremos
            // use appropriate location if you are using MacOS or Linux
            f = fopen("/etc/group", "r");

            if (f == NULL)
            {
                printf("Error al abrir el fichero /etc/group");
                exit(-1);
            }

            char buffer[256];
            char *groupname;
            char *password;
            char *groupid;
            char *groupmembers;
            printf("Grupo:\n");
            printf("-----------------------------------------\n");
            while (fgets(buffer, 256, f) != NULL) //Leemos el fichero en bucle
            {
                groupname = strtok(buffer, ":");
                password = strtok(NULL, ":");
                groupid = strtok(NULL, ":");
                strtok(NULL, ":");
                groupmembers = strtok(NULL, ":");
                //Se imprime el campo de la estructura que nos interesa
                printf("Nombre del grupo principal: %s\n", groupname);
                printf("Contraseña: %s\n", password);
                printf("GID: %s\n", groupid);
                printf("Miembros secundarios: %s\n", groupmembers);
                printf("-----------------------------------------\n");
            }
            exit(0);
        }

        else //Caso en el que llamemos mal al programa
        {
            printf("No ha llamado bien al programa, utilice las siguientes flags:\n");
            printf("--help, junto con cualquiera (se ignoran las demás)\n");
            printf("--user <usuario>\n");
            printf("--user <usuario> --maingroup\n");
            printf("--active\n");
            printf("--active --maingroup\n");
            printf("--group <grupo>\n");
            printf("--allgroups\n");
            exit(-1);
        }
    }
    exit(0);
}