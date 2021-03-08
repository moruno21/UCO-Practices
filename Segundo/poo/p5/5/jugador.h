//Archivo jugador.h
//Contiene la clase jugador

#ifndef JUGADOR_H
#define JUGADOR_H
#include "persona.h"        //Incluimos el archivo persona.h para poder realizar la herencia
#include <list>
#include <fstream>
#include <iostream>


struct Apuesta{             //Creamos la structura apuesta para posteriormente declarar la lista de apuestas
    int tipo;               //Tipo de apuesta
    std::string valor;      //Apuesta realizada (rojo, negro, pares, 17...)
    int cantidad;           //Cantidad de dinero apostada
};

class Jugador: public Persona {     //Clase Jugador que hereda de la clase Persona
    
    private:

    int dinero_;                    //Dinero del jugador
    std::string codigo_;            //Codigo del jugador
    std::list<Apuesta> apuestas_;   //Lista de tipo Apuesta

    public:

        //Constructor que hereda parametros de la clase persona, asigna el codigo y pone el dinero a 1000 a un jugador
        inline Jugador(std::string dni, std::string codigo, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad ="", std::string provincia="", std::string pais= "", int dinero= 1000):Persona(dni, nombre, apellidos, edad, direccion, localidad, provincia, pais){
            codigo_ = codigo;
            dinero_ = dinero;
        };

        inline void setDinero(int const &dinero){dinero_ = dinero;}                 //Función modificadora del dinero
        inline void setCodigo(std::string const &codigo){ codigo_ = codigo;}        //Función modificadora del código
        void setApuestas();                                                         //Función modificadora de las apuestas
        
        inline int getDinero() const { return dinero_;}                             //Función observadora del dinero
        inline std::string getCodigo() const { return codigo_;}                     //Función observadora del codigo
        inline std::list<Apuesta> getApuestas() const { return apuestas_;}          //Función observadora de las apuestas

};

#endif