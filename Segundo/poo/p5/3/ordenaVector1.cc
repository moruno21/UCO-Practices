//Archivo ordenaVector1.cc
//Programa que pide al usuario rellenar un vector. Este se ordena y se muestra por pantalla

#include <iostream>
#include <algorithm>                                                                    //Biblioteca que incluye la funcion sort

int main(){
    int n;                                                                              //Tamaño que tendra nuestro vector
    int v[n];                                                                           //Vector de enteros de tamaño n
    std::cout<<"Introduzca el tamaño del vector"<<std::endl;
    std::cin>>n;                                                                        //Introducimos el tamaño del vector
    
    std::cout<<"Introduzca los elementos del vector"<<std::endl;                        
    for(int i=0; i<n; i++){                                                             //Introducimos los elementos del vector                                              
        std::cin>>v[i];
    }
    
    std::sort(v, v+n);                                                                  //Ordenamos los elementos del vector con la funcion sort

    std::cout<<"El vector ordenado es:"<<std::endl;
    for(int i=0; i<n; i++){                                                             //Mostramos el vector ordenado por pantalla
        std::cout<<v[i]<<"|";
    }

    std::cout<<std::endl;
    std::cout<<"Fin del programa"<<std::endl;
    return 0;                                                                           //Salimos del programa
}