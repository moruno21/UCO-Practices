//Archivo guess.cc
//Programa en el que el usuario trata de adivinar el numero pseudoaleatorio generado

#include <iostream>
#include <cstdlib>
#include <ctime>


int main () {
    srand(time(NULL));                                                              //Plantamos la semilla del numero pseudoaleatorio
    int n = 1 + rand() % (11 - 1);                                                  //Generacion del numero pseudoaleatorio del 1 al 10
    int a;                                                                          //Numero introducido por el usuario

    std::cout<<"Programa para adivinar un número del 1 al 10"<<"\n";
    std::cout<<"Introduzca el número para tratar de adivinarlo: ";
    std::cin>> a;
    std::cout<<"\n";

    while ( a != n ){                                                               //Mientras el usuario no adivine el número, seguirá metido en el bucle while
        if ( a > n ){
            std::cout<<"Error, el numero a adivinar es menor. Pruebe de nuevo: ";
            std::cin>> a;
            std::cout<<"\n";
        }
        if ( a < n ){
            std::cout<<"Error, el numero a adivinar es mayor. Pruebe de nuevo: ";
            std::cin>> a;
            std::cout<<"\n";
        } 
    }                                                                               //Saldrá del bucle solo cuando adivine el número, por lo tanto cuando lo haga, se imprimirá lo siguiente por pantalla

    std::cout<<"Enhorabuena, el numero era el "<< a <<"\n";
    std::cout<<"Fin del programa"<<"\n";
}