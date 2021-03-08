//Archivo jugador-ppal.cc
//Programa para probar el funcionamiento de la clase jugador

#include <iostream>
#include "jugador.h"

int main(){
    std::string dni;               //DNI de la persona
    std::string codigo;            //Codigo del jugador
    std::list<Apuesta> apuestas;   //Lista de tipo Apuesta

    std::cout<<"Programa para comprobar el funcionamiento de la clase jugador"<<std::endl;
    std::cout<<"Introduzca los datos del jugador"<<std::endl;
    
    //Introduciremos el DNI 33XX para que el programa lea las apuestas del fichero 33XX.txt

    std::cout<<"DNI: ";
    std::cin>>dni;
    std::cout<<"Codigo: ";
    std::cin>>codigo;
    std::cout<<std::endl;

    Jugador j(dni, codigo);                                         //Creamos el jugador

    j.setApuestas();                                                //El jugador hace sus apuestas
    apuestas = j.getApuestas();                                     //Copiamos las apuestas en la lista apuestas

    int n=1;                                                        //La usamos para saber en que apuesta estamos
    for(auto i= apuestas.begin(); i!=apuestas.end(); i++){          //Imprimimos todas las apuestas del jugador
        std::cout<<"Apuesta "<<n<<": "<<std::endl;
        std::cout<<"- Tipo: "<<i->tipo<<std::endl;
        std::cout<<"- Valor: "<<i->valor<<std::endl;
        std::cout<<"- Cantidad: "<<i->cantidad<<std::endl;
        std::cout<<std::endl;
        n++;
    }

    return 0;

}