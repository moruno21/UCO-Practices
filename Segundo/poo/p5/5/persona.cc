//Archivo persona.cc
//Contiene el cuerpo de las funciones de la clase Persona

#include "persona.h"
#include <string>

//Constructor. Asigna todos los valores que le pasemos a un objeto de la clase Persona
Persona::Persona(std::string dni, std::string nombre, std::string apellidos, int edad, std::string direccion, std::string localidad, std::string provincia, std::string pais){
    dni_=dni;
    nombre_=nombre;
    apellidos_=apellidos;
    edad_=edad;
    direccion_=direccion;
    localidad_=localidad;
    provincia_=provincia;
    pais_=pais;
}

//Funcion que hace que se introduzcan edades mayores o iguales a 0
bool Persona::setEdad(int const &edad){
    if (edad>=0){
        edad_=edad;
        return true;
    }
    return false;
}

//Función para comprobar si la persona es o no mayor de edad
bool Persona::mayor() const{
    if (edad_<18){
        return false;
    }
    return true;
}

