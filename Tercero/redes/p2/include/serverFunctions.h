#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include "./game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <cstring>
#include <regex>
#include <ctype.h>
#include <regex.h>

using namespace std;

class User
{
private:
    string username;
    string password;
    bool hasEnteredTheSystem;
    int sd;

public:
    User(string username, string password, int sd)
    {
        this->setUsername(username);
        this->setPassword(password);
        this->setSd(sd);
        this->hasEnteredTheSystem = false;
    }

    User()
    {
        this->username = "";
        this->password = "";
    }

    string getUsername() { return this->username; };
    string getPassword() { return this->password; };
    int getSd() { return this->sd; }
    bool getHasEnteredTheSystem() { return this->hasEnteredTheSystem; }

    void setUsername(string newUsername) { this->username = newUsername; }
    void setPassword(string newPassword) { this->password = newPassword; }
    void setSd(int sd) { this->sd = sd; }
    void setHasEnteredTheSystem(bool hasEnteredTheSystem) { this->hasEnteredTheSystem = hasEnteredTheSystem; }
};

vector<User> loadUsersFromFile();                    //Returns a list of users load from a file
bool registerNewUser(User user, vector<User> users); //Adds a new user to the file in case it is not repeated

bool passwordMatchWithUsername(string password, string username, vector<User> users); //Checks if the password given matches with its username
bool usernameExists(string username, vector<User> users);                             //Checks if a username is already in use
bool userHasAlreadySignIn(string username, vector<User> usersConnected);              //Checks if the username has already sign up

void sendMessage(string message, int i); //Sends a message through the socket descriptor i

int inWhichGameAmI(int sd, vector<Game> games);

void manejador(int signum);
void salirCliente(int socket, fd_set *readfds, int *numClientes, int arrayClientes[]);

#endif