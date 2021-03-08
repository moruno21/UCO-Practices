//Archivo ej7.cc
//Contiene el desarrollo del ejercicio 7 de la práctica 5

#include <iostream>

template <class T> 
    
class MiClase{
    private:
        T x_, y_;
    public:
        MiClase (T a, T b){ x_=a; y_=b;};
        T div(){return x_/y_;};
};

int main(){
    MiClase <int> iobj(10,3);
    MiClase <double> dobj(3.3, 5.5);

    std::cout << "division entera = " << iobj.div() << std::endl;
    std::cout << "division real = " << dobj.div() << std::endl;

    return 0;
}