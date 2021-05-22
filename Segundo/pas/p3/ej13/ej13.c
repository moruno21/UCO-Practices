#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h>  //Control de errores
#include <string.h> //Para la funcion strerror()

#define MAX_SIZE 1024
#define QUEUE_NAME "/una_cola"
#define MSG_STOP "exit"

int main()
{
    int must_stop = 0; //Para salirnos del bucle
    int status;        //Para el control de errores
    pid_t flag;        //Para el control de errores

    mqd_t mq; // Descriptor de la cola

    char buffer[MAX_SIZE]; // Buffer para la lectura/escritura

    struct mq_attr attr;        // Atributos de la cola, los inicializamos debajo
    attr.mq_maxmsg = 10;        // Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje. Tener en cuenta que debe incluir el '/0'

    char queue_name[100]; // Almacena el nombre de la cola

    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER")); // Nombre para la cola. Al concatenar el login, sera unica en un sistema compartido.

    pid_t rf = fork();
    switch (rf)
    {
    case -1: //Caso de error
        printf("No he podido crear el proceso hijo \n");
        exit(1);

    case 0: // Hijo. El hijo solo se encargará de escribir.

        /* Apertura de la cola
                O_CREAT: si no existe, se crea
                O_RDWR: lectura/escritura
                O_RDONLY: solo lectura
                O_WRONLY: solo escritura
                0644: permisos rw-r--r--
                        permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
                attr: estructura con atributos para la cola  */

        mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr); //Abrimos la cola
        printf("[HIJO]: El nombre de la cola es: %s\n", queue_name);
        printf("[HIJO]: El descriptor de la cola es: %d\n", (int)mq);

        if (mq == -1)
        {
            perror("[HIJO]: Error en la apertura de la cola");
            exit(-1);
        }
        printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

        printf("[HIJO]: Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
        do
        {
            printf("[HIJO]> ");

            /* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
                    It stops when either (n-1) characters are read, the newline character is read,
                    or the end-of-file is reached, whichever comes first.
                    Automáticamente fgets inserta el fin de cadena '\0'
                    */
            fgets(buffer, MAX_SIZE, stdin);

            // Enviar y comprobar si el mensaje se manda
            if (mq_send(mq, buffer, MAX_SIZE, 0) != 0)
            {
                perror("[HIJO]: Error al enviar el mensaje");
                exit(-1);
            }
            if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0) // Si lo que hemos introducido es exit, salimos
                must_stop = 1;

            ssize_t bytes_read; // Número de bytes leidos

            bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); // Recibir el mensaje

            if (bytes_read < 0) // Comprobar que la recepción es correcta (bytes leidos no son negativos)
            {
                perror("[HIJO]: Error al recibir el mensaje");
                exit(-1);
            }
            // Cerrar la cadena
            //buffer[bytes_read] = '\0';
            printf("%s\n", buffer);

            // Iterar hasta escribir el código de salida
        } while (!must_stop);

        // Cerrar la cola
        if (mq_close(mq) == -1)
        {
            perror("[HIJO]: Error cerrando la cola");
            exit(-1);
        }
        printf("[HIJO]: Cola cerrada.\n");
        exit(0);
        break; //Saldría de este caso del switch

    default: // Padre. El padre solo se encargará de leer

        mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr); //Abrimos la cola
        printf("[PADRE]: El nombre de la cola es: %s\n", queue_name);
        printf("[PADRE]: El descriptor de la cola es:%d\n", (int)mq);

        if (mq == -1) //Control de errores
        {
            perror("[PADRE]: Error en la apertura de la cola");
            exit(-1);
        }

        printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
        printf("[PADRE]: Recibiendo mensaje (espera bloqueante)...\n");

        do
        {
            ssize_t bytes_read; // Número de bytes leidos

            bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); // Recibir el mensaje

            if (bytes_read < 0) // Comprobar que la recepción es correcta (bytes leidos no son negativos)
            {
                perror("[PADRE]: Error al recibir el mensaje");
                exit(-1);
            }
            // Cerrar la cadena
            //buffer[bytes_read] = '\0';

            if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0) // Comprobar el fin del bucle, es decir, si hemos introducido exit
                must_stop = 1;
            else // Si no hemos introducido exit, entramos
                printf("[PADRE]: Recibido el mensaje: %s", buffer);

            sprintf(buffer, "[HIJO]: Número de caracteres recibidos por mi padre: %ld", (strlen(buffer) - 1));

            if (mq_send(mq, buffer, MAX_SIZE, 0) != 0) // Enviar y comprobar si el mensaje se manda
            {
                perror("[PADRE]: Error al enviar el mensaje");
                exit(-1);
            }

        } while (!must_stop); // Iterar hasta que llegue el código de salida, es decir, la palabra exit

        if (mq_close(mq) == -1) // Cerrar la cola
        {
            perror("[PADRE]: Error cerrando la cola");
            exit(-1);
        }
        printf("[PADRE]: Cola cerrada.\n");

        if (mq_unlink(queue_name) == -1) // Eliminar la cola
        {
            perror("[PADRE]: Error eliminando la cola");
            exit(-1);
        }

        //Control de errores
        /*Espera del padre a los hijos*/
        while ((flag = wait(&status)) > 0)
        {
            if (WIFEXITED(status))
                printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
            else if (WIFSIGNALED(status)) //Para seniales como las de finalizar o matar
                printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
        }
        if (flag == (pid_t)-1 && errno == ECHILD)
            printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
        else
        {
            printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    exit(0);
}