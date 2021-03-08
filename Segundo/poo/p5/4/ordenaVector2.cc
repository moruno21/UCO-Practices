//Archivo ordenaVector2.cc
//Programa que pide al usuario rellenar un vector. Este se ordena de forma ascendente o descendente y se muestra por pantalla

#include <iostream>
#include <algorithm>                                                        //Biblioteca que incluye la funcion sort

bool descendente(int i, int j){return i>j;}

int main(){
    int n;                                                                  //Tamaño que tendra nuestro vector
    std::cout<<"Introduzca el tamaño del vector: ";
    std::cin>>n;                                                            //Introducimos el tamaño del vector
    int v[n];                                                               //Vector de enteros de tamaño n
    
    std::cout<<"Introduzca los elementos del vector: "<<std::endl;                        
    for(int i=0; i<n; i++){                                                 //Introducimos los elementos del vector                                              
        std::cin>>v[i];
    }
    
    int opcion;                                                                                         //Opcion para ordenar el vector de manera ascendente o descendente
    std::cout<<"¿Como quiere ordenar el vector? Introduzca 1 para ascendente o 2 para descendente: ";  
    std::cin>>opcion;                                                                                   //Introducimos la opcion
    
    if(opcion==1){
        std::sort(v, v+n);                                      //Ordenamos los elementos del vector con la funcion sort de forma ascendente

        std::cout<<"El vector ordenado ascendente es: |";
        for(int i=0; i<n; i++){                                 //Mostramos el vector ordenado ascendente por pantalla
            std::cout<<v[i]<<"|";
        }
        std::cout<<std::endl;
    }   

    else if (opcion==2){
        std::sort(v, v+n, descendente);                         //Ordenamos los elementos del vector con la funcion sort de forma descendente

        std::cout<<"El vector ordenado descendente es: |";
        for(int i=0; i<n; i++){                                 //Mostramos el vector ordenado descendente por pantalla
            std::cout<<v[i]<<"|";
        }
        std::cout<<std::endl;
    }                   

    std::cout<<"Fin del programa"<<std::endl;
    return 0;                                                   //Salimos del programa
}