#include "./include/serverFunctions.h"

void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[])
{
    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket, readfds);

    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j + 1]);

    (*numClientes)--;

    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Desconexión del cliente: %d\n", socket);

    for (j = 0; j < (*numClientes); j++)
        if (arrayClientes[j] != socket)
            send(arrayClientes[j], buffer, sizeof(buffer), 0);
}

void manejador(int signum)
{
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT, manejador);
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}

vector<User> loadUsersFromFile()
{
    vector<User> users; //List of users
    User user = User(); //Aux user that we will push to the list
    string aux;         //Here we store the values we read from the file
    size_t len = 0;     //Para empezar al principio de cada linea en el fichero

    string filename("./database/registered_users.txt"); //Name of the file
    ifstream f(filename);                               //Open the file
    if (!f)
        EXIT_FAILURE;

    getline(f, aux, ' ');

    while (!f.eof())
    { //Iteramos y metemos los usuarios en el vector de usuarios
        user.setUsername(aux);
        getline(f, aux, '\n');
        user.setPassword(aux);
        users.push_back(user);
        getline(f, aux, ' ');
    }

    f.close();
    return users;
}

bool registerNewUser(User user, vector<User> users)
{
    if (usernameExists(user.getUsername(), users)) //We first check if the user already exists
        return false;
    string filename("./database/registered_users.txt"); //File name
    ofstream f;                                         //Create f
    f.open(filename, ios::app);                         //Open the file to add text
    if (f.fail())
        EXIT_FAILURE;

    f << "\n"
      << user.getUsername();
    f << " ";
    f << user.getPassword();

    f.close();

    return true;
}

bool usernameExists(string username, vector<User> users)
{
    for (int i = 0; i < users.size(); i++) //Iterate the list looking for the name
        if (users[i].getUsername() == username)
            return true;
    return false;
}

bool passwordMatchWithUsername(string password, string username, vector<User> users)
{
    for (int i = 0; i < users.size(); i++)
        if (users[i].getUsername() == username)
            if (users[i].getPassword() == password)
                return true;
    return false;
}

bool userHasAlreadySignIn(string username, vector<User> usersConnected)
{
    for (int i = 0; i < usersConnected.size(); i++)
        if (username == usersConnected[i].getUsername())
            return true;
    return false;
}

void sendMessage(string message, int i) //Sends a message through the socket descriptor i
{
    char buffer[256];
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, message.c_str());
    send(i, buffer, sizeof(buffer), 0);
}

int inWhichGameAmI(int sd, vector<Game> games)
{
    int actualGame = -1;
    for (int i = 0; i < games.size(); i++)
        if (games[i].getSdPlayerOne() == sd || games[i].getSdPlayerTwo() == sd) //We check if the player is one of the game player
            actualGame = i;

    return actualGame;
}
