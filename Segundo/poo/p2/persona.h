//Archivo persona.h
//Contiene la clase Persona

#ifndef PERSONA_H
#define PERSONA_H
#include <string>

class Persona {
    private:
    
        std::string dni_;           //DNI de la persona
        std::string nombre_;        //Nombre de la persona
        std::string apellidos_;     //Apellido de la persona
        int edad_;                  //Edad de la persona
        std::string direccion_;     //Dirección de la persona
        std::string localidad_;     //Localidad de la persona
        std::string provincia_;     //Provincia de la persona
        std::string pais_;          //País de la persona

    public:
        
        inline void setDNI(std::string const &dni){ dni_=dni; }                               //Funcion modificadora del DNI
        inline void setNombre(std:: string const  &nombre){ nombre_=nombre; }                 //Funcion modificadora del nombre
        inline void setApellidos(std::string const &apellidos){apellidos_=apellidos; }        //Funcion modificadora del apellidos
        bool setEdad(int const &edad);                                                        //Funcion modificadora del edad
        inline void setDireccion(std::string const &direccion){ direccion_=direccion; }       //Funcion modificadora del dirección
        inline void setLocalidad(std::string const &localidad){ localidad_=localidad; }       //Funcion modificadora del localidad
        inline void setProvincia(std::string const &provincia){ provincia_=provincia; }       //Funcion modificadora del provincia
        inline void setPais(std::string const &pais){ pais_=pais; }                           //Funcion modificadora del pais
        
        inline std::string getDNI() const { return dni_; }                                          //Funcion observadora del DNI
        inline std::string getNombre() const { return nombre_; }                                    //Funcion observadora del nombre
        inline std::string getApellidos() const { return apellidos_; }                              //Funcion observadora del apellidos
        inline int getEdad() const { return edad_;}                                                 //Funcion observadora del edad
        inline std::string getDireccion() const { return direccion_; }                              //Funcion observadora del dirección
        inline std::string getLocalidad() const { return localidad_; }                              //Funcion observadora del localidad
        inline std::string getProvincia() const { return provincia_; }                              //Funcion observadora del provincia
        inline std::string getPais() const { return pais_;}                                         //Funcion observadora del país
        inline std::string getApellidosyNombre() const { return apellidos_ + ", " + nombre_ ; }     //Funcion observadora del nombre completo

        bool mayor() const ;   //Función para comprobar si la persona es o no mayor de edad

        //Constructor con dni como parametro obligatorio y los demas como parametros opcionales
        Persona (std::string dni, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad ="", std::string provincia="", std::string pais= "");
};

#endif