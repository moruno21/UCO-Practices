//Archivo jugador.cc
//Contiene el cuerpo de las funciones de la clase Jugador

#include "jugador.h"

void Jugador::setApuestas(){                    //Función modificadora de las apuestas
    apuestas_.clear();                          //Vacía la lista de apuestas
    std::ifstream f((getDNI() + ".txt"));       //Se crea el fichero con el DNI del jugador como nombre
    
    if (!f) {                                   //Si hay algun fallo al abrirlo, devolvemos el error
        EXIT_FAILURE; 
    }
    
    Apuesta apuesta;                            //Creamos la estructura apuesta para almacenar temporalmente la información
    std::string cadena;                         //Creamos una cadena para almacenar la información leida del fichero
    getline(f, cadena, ',');                    //Leemos f y almacenamos en cadena hasta llegar a la primera coma
                   
    while (!f.eof()){                           //Este bucle se repetirá hasta que hallamos llegado al final del fichero y no hay nada mas que leer

        apuesta.tipo = std::stoi(cadena);       //Guardamos en tipo el tipo de apuesta haciendo un casting a int
        getline(f, cadena, ',');                //Leemos del archivo hasta la siguiente coma
        
        apuesta.valor = cadena;                 //Guardamos el valor de la apuesta en valor. No hace falta casting ya que es un string
        getline(f, cadena, '\n');               //Buscamos el ultimo elemento de la fila
        
        apuesta.cantidad = std::stoi(cadena);   //Guardamos en cantidad el dinero apostado haciendo un casting a int
        apuestas_.push_back(apuesta);           //Añadimos la apuesta completa a la lista de apuestas
        
        getline(f, cadena, ',');                //Leemos del archivo hasta la siguiente coma
    }
    
    f.close();                                  //Cuando salgamos del while es porque ya no hay más que leer, por lo que cerramos el fichero                      
}