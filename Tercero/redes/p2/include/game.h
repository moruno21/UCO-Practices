#ifndef GAME_H
#define GAME_H

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
#include <algorithm>

using namespace std;

class Game
{
private:
    int sdPlayerOne; //Sd of the first player
    int sdPlayerTwo; //Sd of the second player

    int playerOnePoints; //Points of the first player
    int playerTwoPoints; //Points of the second player

    string sentence;       //Sentence without being encripted
    string secretSentence; //Secret sentence

    vector<string> lettersIntroduced; //Vector with all the letters that Player have introduced

public:
    Game()
    {
        this->sdPlayerOne = -1;
        this->sdPlayerTwo = -1;
        this->playerOnePoints = 0;
        this->playerTwoPoints = 0;
        this->sentence = "";
        this->secretSentence = "";
    }

    Game(int sdPlayerOne, int sdPlayerTwo)
    {
        this->sdPlayerOne = sdPlayerOne;
        this->sdPlayerTwo = sdPlayerTwo;
        this->playerOnePoints = 0;
        this->playerTwoPoints = 0;
        this->sentence = getRandomSentenceFromFile();
        this->setSecretSentence();
    }

    inline int getSdPlayerOne() { return this->sdPlayerOne; }
    inline int getSdPlayerTwo() { return this->sdPlayerTwo; }
    void setSdPlayerOne(int PlayerOne) { this->sdPlayerOne = PlayerOne; }
    void setSdPlayerTwo(int PlayerTwo) { this->sdPlayerTwo = PlayerTwo; }

    inline int getPlayerOnePoints() { return this->playerOnePoints; }
    inline int getPlayerTwoPoints() { return this->playerTwoPoints; }
    void setPlayerOnePoints(int PlayerOne) { this->playerOnePoints = PlayerOne; }
    void setPlayerTwoPoints(int PlayerTwo) { this->playerTwoPoints = PlayerTwo; }

    inline string getSentence() { return this->sentence; }
    inline string getSecretSentence() { return this->secretSentence; }
    inline void setSentence(string sentence) { this->sentence = sentence; }
    inline void setSecretSentence() { this->secretSentence = this->EncriptSentence(this->sentence); }

    inline vector<string> getlettersIntroduced() { return this->lettersIntroduced; } //We get all the letters that have been introduced
    void setLetterIntroduced(string letter);                                         //Introduces a new letter
    bool hasIntroducedLetter(string letter);                                         //Checks if a letter has been introduced

    string getRandomSentenceFromFile();      //Returns a sentence choosen randomly from the file
    string EncriptSentence(string sentence); //Returns the encripted sentence

    bool letterIsInSentence(string letter); //Returns true if letter is in sentence
    int howManyTimesLetterInSentence(string letter);

    void sustituteSentence(string letter); //Change the _ with the letter

    int pair(int sd); //It returns the pair of the user sd (if player1sd = sd, we return player2sd)
};

bool isConsonant(string c); //Returns true if it is a consonant
bool isVowel(string c);     //Returns true if it is a vowel

int puntuation(int playerPoints, string letter, string secretSentence); //Returns the user points

string game(int i, string sentence, string secretSentece, char buffer[]); //Game itself. It returns the string changed with the letter given in buffer
#endif