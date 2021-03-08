//Archivo ej6.cc
//Contiene el desarrollo del ejercicio 6 de la práctica 5

#include <iostream>

template <class tipo>

void imprimeVector(tipo v[], int t){
    for(int i=0; i<t; i++) std::cout<<v[i]<<" ";
    std::cout<<std::endl;
}

int main(){
    int i[6]={1,6,3,6,2,2};
    float f[4]={1.1,6.88,3.1,6.5};
    char c[7]="Moruno";

    imprimeVector(i,6);
    imprimeVector(f,4);
    imprimeVector(c,7);

    return 0;

}