//Archivo juego.cc
//Programa principal prueba funcionamiento de la clase Dados mediante el uso de un menú

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dados.h"
#define NULL__null

int main(){
    Dados d;                                                                                    //Automáticamente se llama al constructor al declarar un objeto de la clase Dados
    int opt=0;                                                                                  //Damos un valor por defecto a opt para que entre en el ciclo while

    std::cout<<"Menú para comprobar el correcto uso de Dados"<<std::endl;
    
    while (opt!=10){                                                                             //Mientras que el usuario no introduzca la opcion de salir, se mostrarán siempre las opciones del menú para que el usuario siga navegando por él

        std::cout<<"----------------------------------------------------------"<<std::endl;
        std::cout<<"| Pulse una opción                                        |"<<std::endl;
        std::cout<<"| 1. Mostrar el valor de los dados                        |"<<std::endl;
        std::cout<<"| 2. Lanzar dados                                         |"<<std::endl;
        std::cout<<"| 3. Mostrar la media de los dados                        |"<<std::endl;
        std::cout<<"| 4. Modificar el valor del primer dado                   |"<<std::endl;
        std::cout<<"| 5. Modificar el valor del segundo dado                  |"<<std::endl;
        std::cout<<"| 6. Mostrar la suma de los dados                         |"<<std::endl;
        std::cout<<"| 7. Mostrar la diferencia de los dados                   |"<<std::endl;
        std::cout<<"| 8. Mostrar cuantas veces se han lanzado los dados       |"<<std::endl;
        std::cout<<"| 9. Mostrar los ultimos 5 valores de ambos dados         |"<<std::endl;
        std::cout<<"| 10. Salir                                               |"<<std::endl;
        std::cout<<"----------------------------------------------------------"<<std::endl;

        std::cin>>opt;                                                                          //El usuario introduce la opción que desee
        std::cout<<"----------------------------------------------------------"<<std::endl;

        switch (opt){                                                                           //Según la opción introducida, se entrará a un caso del switch u a otro

            case 1:
                std::cout<<"El valor del primer dado es "<<d.getDado1()<<"\n";                  //Imprimimos valor del dado 1
                std::cout<<"El valor del segundo dado es "<<d.getDado2()<<"\n";                 //Imprimimos valor del dado 2
            break;
            
            case 2: 
                d.lanzamiento();                                                                //Lanzamos los dados
                std::cout<<"Lanzamiento de dados completado con éxito"<<"\n";
            break;

            case 3:
                std::cout<<"La media del dado 1 es "<<d.getMedia1()<<"\n";                      //Imprimimos el valor de la media de valores del dado 1
                std::cout<<"La media del dado 2 es "<<d.getMedia2()<<"\n";                      //Imprimimos el valor de la media de valores del dado 2
            break;

            case 4:
                int a;
                std::cout<<"Introduzca el nuevo valor del primer dado: ";
                std::cin>>a;                                                                 //Modificamos el dado 1
                if (d.setDado1(a)==true){
                    std::cout<<"Dado guardado correctamente \n";
                }
                else {
                    std::cout<<"ERROR. No se ha podido guardar el dado \n";
                }
            break;
                
            case 5:
                int b;
                std::cout<<"Introduzca el nuevo valor del segundo dado: ";
                std::cin>>b;                                                                //Modificamos el dado 2
                if (d.setDado2(b)==true){
                    std::cout<<"Dado guardado correctamente \n";
                }
                else {
                    std::cout<<"ERROR. No se ha podido guardar el dado \n";
                }
            break;

            case 6: 
                std::cout<<"El valor de la suma es "<<d.getSuma()<<"\n";                        //Imprimimos el valor de la suma de ambos dados
            break ;
            
            case 7: 
                std::cout<<"El valor de la diferencia es "<<d.getDiferencia()<<"\n";            //Imprimimos el valor de la diferencia de ambos dados
            break ;

            case 8: 
                std::cout<<"El dado 1 se ha lanzado "<<d.getLanzamientos1()<<" veces \n";       //Imprimimos cuantas veces se ha lanzado el dado 1
                std::cout<<"El dado 2 se ha lanzado "<<d.getLanzamientos2()<<" veces \n";       //Imprimimos cuantas veces se ha lanzado el dado 2
            break ;

            case 9:
                int v1[5];                                                                      //Creamos un vector donde copiaremos los ultimos 5 valores del dado 1  
                int v2[5];                                                                      //Creamos un vector donde copiaremos los ultimos 5 valores del dado 2

                d.getUltimos1(v1);                                                              //Llamamos a la funcion getUltimos1 y le pasamos v1 para que guarde ahi los ultimos 5 valores del dado 1
                d.getUltimos2(v2);                                                              //Llamamos a la funcion getUltimos2 y le pasamos v2 para que guarde ahi los ultimos 5 valores del dado 2

                std::cout<<"Los ultimos 5 valores obtenidos para el dado 1 son: "<<std::endl;   
                std::cout<<"|";
                for (int i=0; i<5; i++){                                                        //Imprimimos los ultimos 5 valores del dado 1
                    std::cout<<v1[i]<<"|";
                }
                std::cout<<std::endl;
                std::cout<<std::endl;

                std::cout<<"Los ultimos 5 valores obtenidos para el dado 2 son: "<<std::endl;   
                std::cout<<"|";
                for (int i=0; i<5; i++){                                                        //Imprimimos los ultimos 5 valores del dado 2
                    std::cout<<v2[i]<<"|";
                }
                std::cout<<std::endl;

            break;

            case 10:                                                                            //Salimos del menu
                std::cout<<"Saliendo del programa. Hasta pronto \n";
            break;

            default:
                std::cout<<"ERROR, introduzca una opcion valida"<<std::endl;
            break;
        }
    }
}