#include "include/serverFunctions.h"
#include "include/game.h"
#include "./gameFunctions.cpp"
#include "./serverFunctions.cpp"

#define MSG_SIZE 350
#define MAX_CLIENTS 30

/*
 * El servidor ofrece el servicio de un chat
 */

void handler(int signum);
void closedClient(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]);

/* 
	Inicializamos las variables del programa                
*/
int sd, new_sd;
struct sockaddr_in sockname, from;
char buffer[MSG_SIZE];
socklen_t from_len;
fd_set readfds, auxfds;
int salida;
int arrayClientes[MAX_CLIENTS];
int numClientes = 0;
int i, j, k;
int recibidos;
char identificador[MSG_SIZE];

int on, ret;

regex_t regex_;
int result;

vector<User> usersRegistered = loadUsersFromFile(); //Stores all the REGISTERED users
vector<User> usersConnected;                        //Stores all the ONLINE users
vector<int> queue;                                  //Stores the players that are waiting for a game
vector<Game> games;                                 //List of games (max 10 games)

int main()
{
    result = regcomp(&regex_, "REGISTRO -u \\w* -p \\w*", REG_EXTENDED);
    // loadSystem();
    /*
      Incializamos los sockets y preparamos el servidor para la lectura
   */

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("–Err. No se puede abrir el socket cliente\n");
        exit(1);
    }

    on = 1;
    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sockname.sin_family = AF_INET;
    sockname.sin_port = htons(2050);
    sockname.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&sockname, sizeof(sockname)) == -1)
    {
        perror("–Err. No se ha podido realizar la operación bind");
        exit(1);
    }

    from_len = sizeof(from);

    if (listen(sd, 1) == -1)
    {
        perror("–Err. No se ha podido realizar la operación listen");
        exit(1);
    }

    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd, &readfds);
    FD_SET(0, &readfds);

    signal(SIGINT, handler);

    while (1)
    {
        //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
        auxfds = readfds;
        salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

        if (salida > 0)
        {
            for (i = 0; i < FD_SETSIZE; i++)
            {
                //Buscamos el socket por el que se ha establecido la comunicación
                if (FD_ISSET(i, &auxfds))
                {
                    if (i == sd)
                    {
                        if ((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1)
                            perror("–Err. No se han podido aceptar peticiones");

                        else
                        {
                            if (numClientes < MAX_CLIENTS)
                            {
                                cout << "+Ok. Usuario conectado" << endl;
                                strcpy(buffer, "+Ok. Usuario conectado\n");
                                usersRegistered = loadUsersFromFile(); //We have to load the file again cause if one user register, then if we open a new client, he wont know about that previous user

                                arrayClientes[numClientes] = new_sd;
                                numClientes++;
                                FD_SET(new_sd, &readfds);

                                send(new_sd, buffer, sizeof(buffer), 0);
                            }
                            else
                            {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "–Err. Ya hay 30 clientes conectados. Inténtelo de nuevo más tarde\n");
                                send(new_sd, buffer, sizeof(buffer), 0);
                                close(new_sd);
                            }
                        }
                    }
                    else if (i == 0)
                    {
                        //Se ha introducido información de teclado
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer), stdin);

                        //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor.
                        if (strcmp(buffer, "SALIR\n") == 0)
                        {
                            handler(SIGINT);
                        }
                    }
                    else
                    {
                        bzero(buffer, sizeof(buffer));
                        recibidos = recv(i, buffer, sizeof(buffer), 0);

                        if (recibidos > 0)
                        {
                            result = regexec(&regex_, buffer, 0, NULL, 0);
                            if (strcmp(buffer, "SALIR\n") == 0)
                                closedClient(i, &readfds, &numClientes, arrayClientes);

                            else if (!result)
                            {
                                string option = buffer;
                                option.pop_back();
                                string username = option.substr(option.find(" -u ") + 4, option.find("-p"));
                                username = username.substr(0, username.find(" "));                             //Stores the username (I know this mehthod is ackward but it doesnt work if i dont do it like that idk)
                                string password = option.substr(option.find(" -p ") + 4, option.length() + 1); //Stores the password

                                if (usernameExists(username, usersRegistered)) //If the user already exists, he cannot register
                                {
                                    strcpy(buffer, "–Err. Usuario ya registrado\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else
                                {
                                    User user; //We create a new user and set him his attributes
                                    user.setUsername(username);
                                    user.setPassword(password);
                                    user.setSd(sd);

                                    registerNewUser(user, usersRegistered); //Add the user to the file
                                    usersRegistered.push_back(user);        //We also add the user to the registered users list
                                    usersConnected.push_back(user);         //We also add the user to the connected users list
                                    strcpy(buffer, "+Ok. Usuario registrado\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            else if (strncmp(buffer, "USUARIO ", strlen("USUARIO ")) == 0)
                            {
                                if (strncmp(buffer, "USUARIO \n", strlen("USUARIO \n")) == 0)
                                {
                                    strcpy(buffer, "-Err. No se ha podido completar el login\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else
                                {
                                    string user_option = buffer;
                                    user_option.pop_back(); //Removes the \n
                                    int pos = user_option.find(" ");
                                    string username = user_option.substr(pos + 1, user_option.length() + 1); //Here we store the username
                                    if (usernameExists(username, usersRegistered))                           //First we have to check if the user exists
                                    {
                                        if (userHasAlreadySignIn(username, usersConnected)) //Then, if the user is already logged in, he cant logged in twice at the same time
                                            strcpy(buffer, "-Err. No se ha podido completar el login\n");

                                        else
                                        {
                                            for (int i = 0; i < usersRegistered.size(); i++) //We look for the user and we set him the sd
                                                if (usersRegistered[i].getUsername() == username)
                                                    usersRegistered[i].setSd(sd);
                                            strcpy(buffer, "+Ok. Usuario correcto\n");
                                        }

                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                    else //The user didnt exist
                                    {
                                        strcpy(buffer, "–Err. Usuario incorrecto\n");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                            }
                            else if (strncmp(buffer, "PASSWORD ", strlen("PASSWORD ")) == 0)
                            {
                                if (strncmp(buffer, "PASSWORD \n", strlen("PASSWORD \n")) == 0)
                                {
                                    strcpy(buffer, "–Err. Error en la validación\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else
                                {
                                    bool userLoggedIn = false;   //Use this to go into the if statement when the user cant log in
                                    string pass_option = buffer; //Here we store PASSWORD p, for example
                                    pass_option.pop_back();      //Removes the \n
                                    int pos = pass_option.find(" ");
                                    string password = pass_option.substr(pos + 1, pass_option.length() + 1); //We store the actual password in password

                                    for (int pos = 0; pos < usersRegistered.size(); pos++) //We look for the user with the user with that password
                                    {
                                        if ((usersRegistered[pos].getPassword() == password) && (usersRegistered[pos].getSd() == sd)) //IMPORTANT: WE HAVE TO LOOK FOR OUR ACTUAL USER. THATS WHY WE USE THE SD
                                        {
                                            strcpy(buffer, "+Ok. Usuario validado\n");
                                            send(i, buffer, sizeof(buffer), 0);
                                            User newUser = usersRegistered[pos];
                                            newUser.setSd(i);
                                            usersConnected.push_back(newUser);
                                            userLoggedIn = true; //User is logged in
                                            break;               //Stop looking for the user
                                        }
                                    }
                                    if (!userLoggedIn) //Password was incorrect
                                    {
                                        strcpy(buffer, "–Err. Error en la validación\n");
                                        send(i, buffer, sizeof(buffer), 0);
                                    }
                                }
                            }
                            else if (strncmp(buffer, "INICIAR-PARTIDA", strlen("INICIAR-PARTIDA")) == 0)
                            {
                                queue.push_back(i);
                                if (queue.size() == 2)
                                {
                                    //TODO we have to check if there are 10 games or less
                                    Game newGame(queue[0], queue[1]);                                                             //we create a new game with the enqueued players
                                    games.push_back(newGame);                                                                     //Adds the game to the list of games
                                    sprintf(buffer, "+Ok. Empieza la partida. FRASE: %s\n", newGame.getSecretSentence().c_str()); //Prints the secret sentence

                                    send(queue[0], buffer, sizeof(buffer), 0); //Sends the sentence to both players
                                    send(queue[1], buffer, sizeof(buffer), 0); //Sends the sentence to both players
                                    queue.clear();                             //We remove both players from the queue
                                }
                                else
                                {
                                    strcpy(buffer, "+Ok. Petición Recibida. quedamos a la espera de más jugadores\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }

                                //TODO Comprobacion para devolver mensaje en caso de que haya mas de 10 partidas
                            }

                            else if (strncmp(buffer, "CONSONANTE ", strlen("CONSONANTE ")) == 0)
                            {
                                int actualGame = inWhichGameAmI(i, games); //Stores in what game are we playing
                                string option = buffer;
                                option.pop_back();
                                int pos = option.find(" ");
                                string c = option.substr(pos + 1, option.length() + 1);
                                if (!isConsonant(c))
                                {
                                    sprintf(buffer, "-Err. %s no es una consonante\n", c.c_str());
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else if (!games[actualGame].hasIntroducedLetter(c)) //If the letter hasn't been introduced
                                {
                                    games[actualGame].setLetterIntroduced(c);                  //We tell the game that the player has introduced the letter c
                                    int n = games[actualGame].howManyTimesLetterInSentence(c); //We count how many times the letter appears in the sentence
                                    if (games[actualGame].getSdPlayerOne() == i)               //We increase the player points
                                        games[actualGame].setPlayerOnePoints(games[actualGame].getPlayerOnePoints() + (50 * n));
                                    else
                                        games[actualGame].setPlayerTwoPoints(games[actualGame].getPlayerTwoPoints() + (50 * n));

                                    games[actualGame].sustituteSentence(c); //We update our secret sentence with the letter guessed by the player

                                    if (games[actualGame].getSentence() == games[actualGame].getSecretSentence()) //If the player has guessed the sentence
                                    {
                                        string winnerUsername;
                                        for (int pos = 0; pos < usersConnected.size(); pos++)
                                            if (usersConnected[pos].getSd() == i)
                                                winnerUsername = usersConnected[pos].getUsername();

                                        int points;
                                        if (games[actualGame].getSdPlayerOne() == i) //We store in points the points of the winner
                                            points = games[actualGame].getPlayerOnePoints();
                                        else
                                            points = games[actualGame].getPlayerTwoPoints();
                                        sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. Ha ganado el jugador %s con %d puntos.\n", games[actualGame].getSentence().c_str(), winnerUsername.c_str(), points);
                                        send(i, buffer, sizeof(buffer), 0);
                                        send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);
                                        games.erase(games.begin() + actualGame);
                                    }
                                    else
                                    {
                                        sprintf(buffer, "+Ok. %s aparece %d veces. FRASE: %s\n", c.c_str(), n, games[actualGame].getSecretSentence().c_str());
                                        send(i, buffer, sizeof(buffer), 0);
                                        send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);
                                    }
                                }
                                else //If the letter has already been introduced
                                {
                                    sprintf(buffer, "-Err. %s ya ha sido introducida\n", c.c_str());
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }
                            else if (strncmp(buffer, "VOCAL ", strlen("VOCAL ")) == 0)
                            {
                                int actualGame = inWhichGameAmI(i, games); //Stores in which postion of the vector games is the game we are playing at
                                string option = buffer;
                                option.pop_back();
                                int pos = option.find(" ");
                                string c = option.substr(pos + 1, option.length() + 1);

                                int pointsOfCurrentPlayer;
                                if (games[actualGame].getSdPlayerOne() == i) //We increase the player points
                                    pointsOfCurrentPlayer = games[actualGame].getPlayerOnePoints();
                                else
                                    pointsOfCurrentPlayer = games[actualGame].getPlayerOnePoints();

                                if (pointsOfCurrentPlayer < 50)
                                {
                                    sprintf(buffer, "+Ok. No tienes puntuación suficiente\n");
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else if (!isVowel(c))
                                {
                                    sprintf(buffer, "-Err. %s no es una vocal\n", c.c_str());
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                                else if (!games[actualGame].hasIntroducedLetter(c)) //If the letter hasn't been introduced
                                {
                                    games[actualGame].setLetterIntroduced(c);                  //We tell the game that the player has introduced the letter c
                                    int n = games[actualGame].howManyTimesLetterInSentence(c); //We count how many times the letter appears in the sentence
                                    games[actualGame].sustituteSentence(c);                    //We update our secret sentence with the letter guessed by the player

                                    if (games[actualGame].getSdPlayerOne() == i) //We increase the player points
                                        games[actualGame].setPlayerOnePoints(games[actualGame].getPlayerOnePoints() - 50);
                                    else
                                        games[actualGame].setPlayerTwoPoints(games[actualGame].getPlayerTwoPoints() - 50);

                                    sprintf(buffer, "+Ok. %s aparece %d veces. FRASE: %s\n", c.c_str(), n, games[actualGame].getSecretSentence().c_str());
                                    send(i, buffer, sizeof(buffer), 0);
                                    send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);
                                    if (games[actualGame].getSentence() == games[actualGame].getSecretSentence())
                                    {
                                        string winnerUsername;
                                        for (int pos = 0; pos < usersConnected.size(); pos++)
                                            if (usersConnected[pos].getSd() == i)
                                                winnerUsername = usersConnected[pos].getUsername();

                                        int points;
                                        if (games[actualGame].getSdPlayerOne() == i) //We store in points the points of the winner
                                            points = games[actualGame].getPlayerOnePoints();
                                        else
                                            points = games[actualGame].getPlayerTwoPoints();

                                        sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. Ha ganado el jugador %s con %d puntos.\n", games[actualGame].getSentence().c_str(), winnerUsername.c_str(), points);
                                        send(i, buffer, sizeof(buffer), 0);
                                        send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);

                                        games.erase(games.begin() + actualGame);
                                    }
                                }
                                else //If the letter has already been introduced
                                {
                                    sprintf(buffer, "-Err. %s ya ha sido introducida\n", c.c_str());
                                    send(i, buffer, sizeof(buffer), 0);
                                }
                            }

                            else if (strncmp(buffer, "RESOLVER ", strlen("RESOLVER ")) == 0)
                            {
                                int actualGame = inWhichGameAmI(i, games); //Stores in which postion of the vector games is the game we are playing at
                                string option = buffer;
                                option.pop_back();
                                int pos = option.find(" ");
                                string sentence = option.substr(pos + 1, option.length() + 1);
                                std::transform(sentence.begin(), sentence.end(), sentence.begin(), ::toupper); //Transform the sentence to uppercase in case the user inserted it in lowercase
                                if (games[actualGame].getSentence() == sentence)
                                {
                                    string winnerUsername;
                                    for (int pos = 0; pos < usersConnected.size(); pos++)
                                        if (usersConnected[pos].getSd() == i)
                                            winnerUsername = usersConnected[pos].getUsername();
                                    int points;
                                    if (games[actualGame].getSdPlayerOne() == i) //We store in points the points of the winner
                                        points = games[actualGame].getPlayerOnePoints();
                                    else
                                        points = games[actualGame].getPlayerTwoPoints();

                                    sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. Ha ganado el jugador %s con %d puntos.\n", games[actualGame].getSentence().c_str(), winnerUsername.c_str(), points);
                                }
                                else
                                    sprintf(buffer, "+Ok. Partida finalizada. FRASE: %s. No se ha acertado la frase\n", games[actualGame].getSentence().c_str());

                                send(i, buffer, sizeof(buffer), 0);
                                send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);
                                games.erase(games.begin() + actualGame);
                            }

                            else if (strncmp(buffer, "PUNTUACION", strlen("PUNTUACION")) == 0)
                            {
                                int actualGame = inWhichGameAmI(i, games); //Stores in which postion of the vector games is the game we are playing at
                                int points;
                                if (games[actualGame].getSdPlayerOne() == i) //We check if we are player 1 or player 2
                                    points = games[actualGame].getPlayerOnePoints();
                                else
                                    points = games[actualGame].getPlayerTwoPoints();

                                sprintf(buffer, "+Ok. Su puntuación es: %d\n", points);
                                send(i, buffer, sizeof(buffer), 0);
                            }
                            else if (strncmp(buffer, "SALIR", strlen("SALIR")) == 0)
                                closedClient(i, &readfds, &numClientes, arrayClientes);
                            else
                            {
                                strcpy(buffer, "--Err. Solicitud rechazada\n");
                                send(i, buffer, sizeof(buffer), 0);
                            }
                        }
                        //Si el cliente introdujo ctrl+c
                        if (recibidos == 0)
                        {
                            //Eliminar ese socket
                            closedClient(i, &readfds, &numClientes, arrayClientes);
                        }
                    }
                }
            }
        }
    }

    close(sd);
    return 0;
}

void closedClient(int socket, fd_set *readfds, int *numClientes, int arrayClientes[])
{
    int actualGame = inWhichGameAmI(i, games);
    printf("El socket %d, se ha desconectado\n", i);
    char buffer[250];
    int j;
    strcpy(buffer, "+Ok. Desconexión procesada.\n");
    send(i, buffer, sizeof(buffer), 0);
    if (actualGame != -1)
    {
        strcpy(buffer, "+Ok. Ha salido el otro jugador. Finaliza la partida\n");
        send(games[actualGame].pair(i), buffer, sizeof(buffer), 0);
    }
    close(socket);
    FD_CLR(socket, readfds);

    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j + 1]);

    (*numClientes)--;
    for (int i = 0; i < usersRegistered.size(); i++) //We assign sd=-1 to the user that is about to exit the program
        if (usersRegistered[i].getSd() == sd)
            usersRegistered[i].setSd(-1);

    for (int i = 0; i < usersConnected.size(); i++) //We delete the user that is about to exit the program from the connected users list
        if (usersConnected[i].getSd() == sd)
            usersConnected.erase(usersConnected.begin() + i);
}

void handler(int signum)
{
    // saveSystem();
    printf("\nApagando el servidor...\n");
    signal(SIGINT, handler);
    for (j = 0; j < numClientes; j++)
    {
        bzero(buffer, sizeof(buffer));
        strcpy(buffer, "–Err. Desconectado por el servidor\n");
        send(arrayClientes[j], buffer, sizeof(buffer), 0);
        close(arrayClientes[j]);
        FD_CLR(arrayClientes[j], &readfds);
    }
    close(sd);
    regfree(&regex_);
    exit(-1);
}
