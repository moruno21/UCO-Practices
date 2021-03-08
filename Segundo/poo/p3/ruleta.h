//Archivo ruleta.h
//Contiene la clase Ruleta

#ifndef RULETA_H
#define RULETA_H
#include <list>
#include <iostream>
#include "jugador.h"    //Incluimos jugador.h para poder declarar objetos de la clase Jugador
#include "crupier.h"    //Incluimos crupier.h para poder declarar objetos de la clase Crupier


class Ruleta {

    private:

        int banca_;                         //Dinero de la banca
        int bola_;                          //Valor de la bola obtenida por la ruleta
        std::list<Jugador> jugadores_;      //Lista de jugadores
        Crupier crupier_;                   //Objeto de la clase Crupier

    public:

        inline Ruleta(Crupier crupier):crupier_(crupier.getDNI(), crupier.getCodigo()){    //Constructor de la clase Ruleta
            bola_=-1;
            banca_=1000000;
        }
        
        inline void giraRuleta(){                                               //Funcion que genera un numero de bola aleatorio
            srand(time(NULL));
            bola_= rand()%(37);
        }

        inline int getBanca() const {return banca_;}                            //Función observadora del valor de banca
        inline int getBola() const {return bola_;}                              //Función observadora del valor de bola
        inline Crupier getCrupier() const {return crupier_;}                    //Función observadora del objeto crupier
        inline std::list<Jugador> getJugadores() const {return jugadores_;}     //Función observadora de la lista de jugadores

        
        bool setBanca(int const &banca);                                        //Función modificadora del valor de banca
        bool setBola(int const &bola);                                          //Función modificadora del valor de bola
        inline void setCrupier(Crupier const &crupier){crupier_=crupier;}       //Función modificadora del objeto crupier

        bool addJugador(Jugador const &jugador);                                //Función que añade un jugador a la lista

        int deleteJugador(std::string const &dni);                              //Función que borra a un jugador de la lista pasando un dni como parámetro
        int deleteJugador(Jugador const &jugador);                              //Función que borra a un jugador de la lista pasando un objeto del tipo Jugador como parámetro

        void escribeJugadores();                                                //Funcion que escribe los datos de la lista de jugadores en un fichero
        void leeJugadores();                                                    //Funcion que escribe los datos de un fichero en la lista jugadores

        void getPremios();                                                      //Funcion que actualiza el dinero ganado o perdido por los jugadores
        
        bool esRoja(int const &valor);                                          //Funcion que determina si la bola es roja o no
        bool esPar(int const &valor);                                           //Funcion que determina si la bola es par o no
        bool esAlta(int const &valor);                                          //Funcion que determina si la bola es un valor alto o no
};
#endif