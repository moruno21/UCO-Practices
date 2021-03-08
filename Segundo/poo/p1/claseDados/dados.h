//Archivo dados.h
//La clase dados representa el lanzamiento de 2 dados

#ifndef DADOS_H
#define DADOS_H
#include <cstdlib>
#include <ctime>
#include <iostream>

class Dados{

    private:
        int d1_;                                    //Dado 1
        int d2_;                                    //Dado 2
        int lanz1_;                                 //Numero de lanzamientos del dado 1
        int lanz2_;                                 //Numero de lanzamientos del dado 2
        int sum1_;                                  //Sumatorio de los valores de2 dado 1
        int sum2_;                                  //Sumatorio de los valores del dado 2
        int ultimos1 [5] = {0,0,0,0,0};             //Aquí almacenaremos de inicio los ultimos 5 valores del dado 1
        int ultimos2 [5] = {0,0,0,0,0};             //Aquí almacenaremos de inicio los ultimos 5 valores del dado 2
        
    public:
       
        Dados();                                                            //Constructor de la clase dados. No devuelve nada

        inline int getDado1() const { return d1_; }                         //Devuelve el valor del primer dado  
        inline int getDado2() const { return d2_; }                         //Devuelve el valor del segundo dado         

        inline int getDiferencia() const { return (abs(d1_ - d2_)); }       //Función que muestra la diferencia entre los dos dados
        inline int getSuma() const { return d1_ + d2_; }                    //Función que muestra la suma de los valores de los dados 1 y 2

        inline int getLanzamientos1() const { return lanz1_; }              //Devuelve el numero de veces que se ha lanzado el dado 1
        inline int getLanzamientos2() const { return lanz2_; }              //Devuelve el numero de veces que se ha lanzado el dado 2

        void lanzamiento();                                                 //Obtiene un nuevo valor aleatorio para los dos dados

        bool setDado1(const int &n);                                        //Asigna un valor al dado uno. Si se asigna correctamente devuelve true. Por el contrario devuelve false
        bool setDado2(const int &n);                                        //Asigna un valor al dado dos. Si se asigna correctamente devuelve true. Por el contrario devuelve false

        float getMedia1() const;                                            //Devuelve la media de los valores obtenidos del dado 1
        float getMedia2() const;                                            //Devuelve la media de los valores obtenidos del dado 2

        void getUltimos1(int v[]);                                          //Guarda en el vector v[] los ultimos 5 valores del dado 1
        void getUltimos2(int v[]);                                          //Guarda en el vector v[] los ultimos 5 valores del dado 2
};

#endif