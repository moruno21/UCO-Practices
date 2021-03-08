//Archivo ordenaJugadores.cc
//Programa que ordena a los jugadores de un vector por su DNI

#include <iostream>
#include <algorithm>
#include <fstream>
#include "jugador.h"
#include <vector>

bool ascendente(Jugador j1, Jugador j2){return j1.getDNI()<j2.getDNI();}                                        //Funcion que pasaremos a sort para que ordene los jugadores por DNI en orden ascendente
bool descendente(Jugador j1, Jugador j2){return j1.getDNI()>j2.getDNI();}                                       //Funcion que pasaremos a sort para que ordene los jugadores por DNI en orden descendente


std::vector<Jugador> leeJugadores(){                                                                            //Funcion que escribe los datos de un fichero en un vector de jugadores
    std::vector<Jugador> jugadores_;
    jugadores_.empty();                                                                                         //Al comienzo, vaciamos el vector de jugadores
    std::ifstream f ("jugadores.txt");                                                                          //Creacion del puntero f para abrir el fichero jugadores.txt en modo lectura
    
    char dni[255], codigo[255], nombre[255], apellidos[255];                                                    //Creamos variables para almacenar temporalmente los datos del jugador
    char direccion[255], localidad[255], provincia[255], pais[255], dinero[255];                                //Creamos variables para almacenar temporalmente los datos del jugador
    
    while(f.getline(dni, 255, ',')){                                                                            //Vamos leyendo el fichero y guardando los valores en las variable char creadas anteriormente                     
        f.getline(codigo, 255, ',');
        f.getline(nombre, 255, ',');
        f.getline(apellidos, 255, ',');
        f.getline(direccion, 255, ',');
        f.getline(localidad, 255, ',');
        f.getline(provincia, 255, ',');
        f.getline(pais, 255, ',');
        f.getline(dinero, 255, '\n');
        Jugador aux (dni, codigo, nombre, apellidos, 0, direccion, localidad, provincia, pais, atoi(dinero));   //Creamos un jugador aux y le pasamos sus datos
        jugadores_.push_back(aux);                                                                              //Pasamos aux a la lista
    }
    f.close();                                                                                                  //Cerramos el fichero
    return jugadores_;                                                                                          //Devolvemos el vector de jugadores                                                                 
} 


int main(){
    std::vector<Jugador> jugadores;
    jugadores = leeJugadores();

    std::cout<<"DNIS del vector de jugadores : "<<std::endl;
    for (int i = 0; i < (int) jugadores.size(); i++){                                                           //Imprimimos por pantalla los dni de los jugadores
        std::cout<<jugadores[i].getDNI()<<std::endl;
    }
    int opcion;                                                                                                 //Opcion para ordenar el vector de manera ascendente o descendente
    std::cout<<"¿Como quiere ordenar el vector? Introduzca 1 para ascendente o 2 para descendente: ";  
    std::cin>>opcion;                                                                                           //Introducimos la opcion
    
    if (opcion==1){
        std::sort(jugadores.begin(), jugadores.end(), ascendente);                                              //Ordenamos el vector de jugadores por su DNI en orden ascendente
    }

    else if(opcion==2){
        std::sort(jugadores.begin(), jugadores.end(), descendente);                                             //Ordenamos el vector de jugadores por su DNI en orden descendente
    }

    std::cout<<"DNIS del vector de jugadores ordenados : "<<std::endl;
    for (int i = 0; i < (int) jugadores.size(); i++){                                                           //Imprimimos por pantalla los dni de los jugadores ya ordenados
        std::cout<<jugadores[i].getDNI()<<std::endl;
    }        

    return 0;                                                                                                   //Salimos del programa
}