#include "include/clientFunctions.h"
#include "./clientFunctions.cpp"

int main(int argc, char const *argv[])
{
    bool usernameWasCorrect = false; //This checks if the user entered a valid username
    bool passwordWasCorrect = false; //This checks if the user entered a valid password
    bool amIPlaying = false;         //This checks if the user is playing
    bool myTurn = false;             //This checks if it is player's turn

    if (argc < 2) //Checks if the program is given a IP
    {
        printf("-Err. Proporciona una IP\n");
        exit(-1);
    }

    int sd;
    struct sockaddr_in sockname;
    char buffer[250];
    socklen_t len_sockname;
    fd_set readfds, auxfds;
    int fin = 0;
    int salida;

    /* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("–Err. No se puede abrir el socket cliente\n");
        exit(1);
    }

    /* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2050);
    sockname.sin_addr.s_addr = inet_addr(argv[1]);

    /* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
    len_sockname = sizeof(sockname);

    if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
    {
        perror("–Err. La conexión no se puedo realizar.");
        exit(1);
    }

    //Inicializamos las estructuras
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);
    FD_SET(sd, &readfds);

    /* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
    LogInInfoMessage();
    do
    {
        auxfds = readfds;
        salida = select(sd + 1, &auxfds, NULL, NULL, NULL);

        if (FD_ISSET(sd, &auxfds)) //The server has sent a message
        {

            bzero(buffer, sizeof(buffer));
            recv(sd, buffer, sizeof(buffer), 0);

            printf("%s", buffer);

            if (strcmp(buffer, "–Err. Demasiados clientes conectados\n") == 0 || strcmp(buffer, "–Err. Desconectado por el servidor\n") == 0)
                break;

            if (strcmp(buffer, "+Ok. Usuario correcto\n") == 0)
            {
                usernameWasCorrect = true;
                printf("Introduzca su contraseña\n");
            }
            if (strcmp(buffer, "+Ok. Usuario validado\n") == 0)
            {
                passwordWasCorrect = true;
                printf("%s", buffer);
                //Add below our after sign in/up interface
                OptionsInfoMessage();
            }

            if (regex_match(buffer, (regex("(^\\+Ok\\. Empieza la partida\\. FRASE\\: [ _A-Z]*\n)"))))
            {
                //Add below our game start interface
                startingGameInterface();

                amIPlaying = true;

                if (myTurn == true)
                    printf("+Ok. Turno de partida\n");

                else if (myTurn == false)
                    printf("+Ok. Turno del otro jugador\n");
            }

            if (strcmp(buffer, "+Ok. Petición Recibida. quedamos a la espera de más jugadores\n") == 0) //Im the first who said to play, so I will be the first to play
                myTurn = true;

            if (regex_match(buffer, (regex("(^\\+Ok\\. [a-zA-Z] aparece 0 veces\\. FRASE\\: [ _A-Z]*\n)")))) //When the player miss (letter is 0 times in sentence)
            {
                //Change the turn
                if (myTurn)
                {
                    printf("+Ok. Turno del otro jugador\n");
                    myTurn = false;
                }
                else
                {
                    printf("+Ok. Turno de partida\n");
                    myTurn = true;
                }
            }

            if (strcmp(buffer, "+Ok. Turno del otro jugador\n") == 0) //If we get this, it isn't our turn
                myTurn = false;

            if (strcmp(buffer, "+Ok. Turno de partida\n") == 0) //If we get this, it is our turn
                myTurn = true;

            if (strcmp(buffer, "+Ok. Desconexión procesada.\n") == 0) //If we get a buffer that starts with this sentence, the client has disconnected
            {
                printf("%s", buffer);
                break;
            }
            if (strncmp(buffer, "+Ok. Ha salido el otro jugador", strlen("+Ok. Ha salido el otro jugador")) == 0) //If we get a buffer that starts with this, the other player disconnected, so the game ends
                amIPlaying = false;

            if (strncmp(buffer, "+Ok. Partida finalizada", strlen("+Ok. Partida finalizada")) == 0) //If we get a buffer that starts with this sentence, the game has ended
            {
                amIPlaying = false;
                myTurn = false;
            }
        }
        else //The client has sent a message
        {
            if (FD_ISSET(0, &auxfds))
            {
                bzero(buffer, sizeof(buffer));
                fgets(buffer, sizeof(buffer), stdin);

                if ((strncmp(buffer, "REGISTRO", strlen("REGISTRO")) == 0) && (usernameWasCorrect == true)) //If we try to register after having introduced an username
                    printf("-Err. Ya está registrado\n");

                else if ((strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0) && (usernameWasCorrect == true)) //If we try to enter a username after having introduced another username before
                    printf("-Err. Ya ha iniciado sesión\n");

                else if ((strncmp(buffer, "PASSWORD", strlen("PASSWORD")) == 0) && (usernameWasCorrect == false)) //If we try to enter a password before introducing an username
                    printf("-Err. No puede introducir la contraseña antes que el nombre de usuario\n");

                else if ((strncmp(buffer, "PASSWORD", strlen("PASSWORD")) == 0) && (passwordWasCorrect == true)) //If we try to enter a password after being registered
                    printf("-Err. Ya ha iniciado sesión\n");

                else if ((strcmp(buffer, "INICIAR-PARTIDA\n") == 0) && (passwordWasCorrect == false)) //If we try to start a game before sign in/up
                    printf("-Err. No puede iniciar partida antes de iniciar sesión\n");

                else if ((strcmp(buffer, "INICIAR-PARTIDA\n") == 0) && (amIPlaying == true)) //If we try to start a game while we are in a game
                    printf("-Err. No puede volver a iniciar partida\n");

                if (((amIPlaying == false) || (myTurn == false)) && regex_match(buffer, (regex("(^(CONSONANTE|VOCAL|RESOLVER|PUNTUACION) (.*)\n)")))) //When the user enters a game option and is not playing or its not his turn
                {
                    if (amIPlaying == false)
                        printf("-Err. Inicie una partida antes.\n");

                    else if (myTurn == false)
                        printf("-Err. No es su turno.\n");
                }
                else
                    send(sd, buffer, sizeof(buffer), 0);
            }
        }
    } while (fin == 0);

    close(sd);
    return 0;
}
