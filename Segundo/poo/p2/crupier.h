//Archivo crupier.h
//Contiene la clase Crupier

#ifndef CRUPIER_H
#define CRUPIER_H
#include "persona.h"            //Incluimos el fichero persona.h para que se pueda realizar la herencia correctamente

class Crupier:public Persona{   //La clase Crupier hereda de la clase Persona la parte publica

    private:

        std::string codigo_;    //Código del crupier
    
    public:

        //Incluimos en el constructor el codigo como parametro obligatorio
        inline Crupier (std::string dni, std::string codigo, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad ="", std::string provincia="", std::string pais= "" ):Persona(dni, nombre, apellidos, edad, direccion, localidad, provincia, pais){
            codigo_=codigo;
        };

        inline std::string getCodigo() const { return codigo_;}                   //Funcion observadora del codigo del crupier
        inline void setCodigo(std::string const &codigo) { codigo_= codigo; }     //Funcion modificadora del codigo del crupier
};

#endif