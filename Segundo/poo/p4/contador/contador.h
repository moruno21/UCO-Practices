//Archivo contador.h
//Contiene la clase contador

#ifndef CONTADOR_H
#define CONTADOR_H
#include <list>

class Contador {
        private:
        int valor_;                     //Entero
        int min_;                       //Valor minimo del entero valor_
        int max_;                       //Valor maximo del entero valor_
        std::list<Contador> lista_;     //Lista del historial de contadores habidos

        void controlValor();            //Funcion que controlara los valores que toma el contador

    public:
        Contador(int valor = 0, int min = 0, int max = 1000);           //Constructor de la clase Contador
        
        Contador operator=(const int &n);                               //Funcion que asigna un entero al contador
        Contador operator=(const Contador &c);                          //Funcion que asigna un contador al contador
        
        Contador operator++(void);                                      //Funcion que devuelve el contador antes de ser aumentado
        Contador operator++(int);                                       //Funcion que aumenta el contador y luego lo devuelve
        
        Contador operator--(void);                                      //Funcion que devuelve el contador antes de ser decrementado
        Contador operator--(int);                                       //Funcion que decrementa el contador y luego lo devuelve

        Contador operator+(const int &n);                               //Funcion que devuelve un contador con la suma de n mas el contador
        friend Contador operator+(const int &n, const Contador &c);     //Funcion que devuelve un contador con la suma de un contador mas n

        Contador operator-(const int &n);                               //Funcion que devuelve un contador con la suma de n mas el contador
        friend Contador operator-(const int &n, const Contador &c);     //Funcion que devuelve un contador con la suma de un contador mas n

        bool undo(const int &n=1);                                      //Funcion que deshace los n ultimos cambios de contador

        inline int get() const {return valor_;}                         //Observador, devuelve el valor actual del contador
};

#endif