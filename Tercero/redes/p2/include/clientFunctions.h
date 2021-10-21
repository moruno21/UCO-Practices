#ifndef CLIENTFUNCTIONS_H
#define CLIENTFUNCTIONS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <regex>

using namespace std;

void LogInInfoMessage();
void OptionsInfoMessage();
void startingGameInterface();

#endif