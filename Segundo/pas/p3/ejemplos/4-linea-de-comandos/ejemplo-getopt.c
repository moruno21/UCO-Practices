/*
Ejemplo extraído del estándar POSIX y glibc.
Enlace a la página de documentación de la implemencación de getopt de glibc:
http://pubs.opengroup.org/onlinepubs/9699919799/functions/getopt.html
http://www.gnu.org/software/libc/manual/html_node/Getopt.html
http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
*/

/*
./a.out
./a.out -a -b
./a.out -a -m
./a.out -a m
./a.out m -a
./a.out -b -c
./a.out -b -c hola
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    bool aflag = false;
    bool bflag = false;
    char *cvalue = NULL;
    int index;
    int c;

    /* IMPORTANTE:
     Las variables optind, optarg, opterr y optopt son variables externas
     incluidas en <unistd.h> */

    /*
     If getopt() does not recognize an option character, it prints an error
     message to stderr, stores the character in optopt, and returns '?'. The
     calling program may prevent the error message by setting opterr to 0 */
    // Prueba a ejecutar el programa comentando esta linea, podrás observar como
    // se obtiene un
    // error por defecto por la salida estandar, en este caso el terminal.
    opterr = 0;

    // "abc:" -> busca como opciones a y b sin argumentos y c con un argumento
    // OBLIGATORIO.
    // ':' indica que la opcion debe llevar un argumento obligario

    /* getopt() internamente reordena los valores de argv, las primeras
     posiciones de argv corresponden a opciones conocidas ("-") y las últimas, a
     partir de optind, a opciones no reconocidas. Por tanto, getopt va iterando
     con las opciones ("-"), y devuelve -1 si ya hemos consultado toda la linea
     de argumentos de opciones ("-"). Sino, devuelve el caracter de opción
     encontrado para caracteres validos o devuelve ? si el caracter no es valido
     segun la cadena especificada.*/
    while ((c = getopt(argc, argv, "abc:")) != -1) {
        // Podemos observar qué pasa con las variables externas que va
        // gestionando
        //   getopt() durante las sucesivas llamadas.
        //   - optind: Indice del siguiente elemento ("-") a procesar del vector
        //   argv[]
        //   - optarg: recoge el valor del argumento obligario de una opcion.
        //   - optopt: recoge el valor de la opcion ("-") cuando es desconocida
        //   (?) o INCOMPLETA
        //             respecto a las opciones indicadas.
        switch (c) {
        case 'a':
            aflag = true; // Bandera que indica que la opción -a se ha pasado por
                       // linea de argumentos
            break;

        case 'b':
            bflag = true;
            break;

        case 'c':
            cvalue = optarg; // En optarg se guarda el valor de argumento
                             // obligatorio que requiere c
            break;

        case '?':              // Opcion no reconocida o INCOMPLETA (sin argumento). Probar
                               // tambien la diferencia entre ejecutar %$>./a.out m   ó
                               // %$>./a.out -m
            if (optopt == 'c') // Para el caso de que 'c' no tenga el argumento
                               // obligatorio.
                fprintf(stderr,
                        "La opción %c requiere un argumento. Valor de opterr = "
                        "%d\n",
                        optopt, opterr);
            else if (isprint(optopt)) // Se mira si el caracter es imprimible
                fprintf(stderr,
                        "Opción desconocida \"-%c\". Valor de opterr = %d\n",
                        optopt, opterr);
            else // Caracter no imprimible o especial
                fprintf(stderr, "Caracter `\\x%x'. Valor de opterr = %d\n",
                        optopt, opterr);
            return 1; // Finaliza el programa

        default:
            abort();
        }
        printf("optind: %d, optarg: %s, optopt: %c, opterr: %d\n\n", optind,
               optarg, optopt, opterr);
    }

    /* Este último bucle controla opciones introducidas por el usuario que no
    hayan sido procesadas por ser no reconocidas al no llevar un guion ("-")
    delante.

    (optind) This variable is set by getopt to the index of the next element of
    the argv array to be processed. Once getopt has found all of the option
    arguments, you can use this variable to determine where the remaining
    non-option arguments begin. The initial value of this variable is 1.
    */

    for (index = optind; index < argc; index++)
        printf("Argumento \"%s\" de la línea de comandos que NO ES UNA "
               "OPCIÓN.\n\n",
               argv[index]);

    // El siguiente condicional permitiría dar un valor por defecto a la opción
    // c. Comprueba y razona si se llegaría a ejecutar y en qué circunstancias
    if (cvalue == NULL)
        cvalue = "ValorPorDefecto";

    // Para visualizar que opciones se han activado y sus argumentos
    printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

    return 0;
}
