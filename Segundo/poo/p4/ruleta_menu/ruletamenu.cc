//Archivo ruletamenu.cc
//Programa que prueba todas las funciones de ruleta mediante un menu interactivo

#include <iostream>
#include "ruleta.h"

int main(){
    Crupier c("1234567", "crupier1");           //Se crea un crupier por defecto
    Ruleta r(c);                                //Se crea una ruleta

    Jugador j1("33XX", "jugador1");             //Se definen 3 jugadores por defecto
    Jugador j2("44XX", "jugador2");
    Jugador j3("55XX", "jugador3");


    std::string dni;                            //Aqui guardaremos el dni que introduzca el usuario para cuando quiera borrar un jugador
    std::list<Jugador> jugadoresActivos_;       //Lista de jugadores auxiliar

    int nJugadores, nLanzamientos, dineroMesa, ganaciaBanca;

    std::cout<<"---------------------------------------------------------"<<std::endl;

    std::cout<<"| Hola, este es un menu para probar la ruleta del casino |"<<std::endl;
    
    int opcion_=0;                              //Opcion que introduce el usuario mas adelante

    while (opcion_!=7){                         //Mientras que la opcion introducida no sea 7 (salir), el usuario no saldra del menu
        std::cout<<"---------------------------------------------------------"<<std::endl;
        std::cout<<"| Introduzca la opcion que desee ejecutar                |"<<std::endl;
        std::cout<<"---------------------------------------------------------"<<std::endl;
        std::cout<<"| 1. Cargar los jugadores del fichero jugadores.txt      |"<<std::endl;
        std::cout<<"| 2. Guardar los jugadores en el fichero jugadores.txt   |"<<std::endl;
        std::cout<<"| 3. Ver el estado de la ruleta                          |"<<std::endl;
        std::cout<<"| 4. Girar ruleta                                        |"<<std::endl;
        std::cout<<"| 5. Eliminar jugador de la mesa                         |"<<std::endl;
        std::cout<<"| 6. Añadir jugador a la mesa                            |"<<std::endl;
        std::cout<<"| 7. Salir                                               |"<<std::endl;
        std::cout<<"---------------------------------------------------------"<<std::endl;

        std::cin>>opcion_;                      //El usuario introduce una opcion

        std::cout<<"---------------------------------------------------------"<<std::endl;

        switch (opcion_){
            case 1:                                                                                                             //Pasamos los datos del fichero a la lista
                std::cout<<"Se van a cargar los jugadores del fichero jugadores.txt a la lista de jugadores"<<std::endl;
                r.leeJugadores();
                std::cout<<"Cargado finalizado con exito"<<std::endl;
            break;

            case 2:                                                                                                             //Pasamos los datos de la lista al fichero
                std::cout<<"Se van a cargar los jugadores de la lista de jugadores al fichero jugadores.txt"<<std::endl;
                r.escribeJugadores();
                std::cout<<"Cargado finalizado con exito"<<std::endl;
            break;
            
            case 3:                                                                                                             //Comprobacion del estado de la ruleta
                r.getEstadoRuleta(nJugadores, dineroMesa ,nLanzamientos, ganaciaBanca);
                std::cout<<"Estado actual de la ruleta:"<<std::endl;
                std::cout<<"Numero de jugadores: "<< nJugadores <<std::endl;
                std::cout<<"Dinero en la mesa:  "<< dineroMesa <<std::endl;
                std::cout<<"Numero de lanzamientos: "<< nLanzamientos <<std::endl;
                std::cout<<"Ganancia de la banca: "<< ganaciaBanca <<std::endl;
            break;

            case 4:                                                                                                             //Se simula un giro de ruleta, y se comprueban los premios                                    
                std::cout<<"A continucion se girara la ruleta"<<std::endl;
                if(r.hayJugadores()==false){
                    std::cout<<"No hay jugadores en la lista"<<std::endl;;
                }

                else{
                    r.giraRuleta();
                    std::cout<<"o Valor de la bola: "<<r.getBola()<<std::endl;
                    r.getPremios();
                    jugadoresActivos_ = r.getJugadores();
                    for(auto i = jugadoresActivos_.begin(); i != jugadoresActivos_.end(); i++){
                        std::cout<<"$ Dinero tras giro de la ruleta del jugador con dni "<<(i->getDNI())<<": "<<(i->getDinero())<<std::endl;
                    }
                    std::cout<<"$$ Dinero banca: "<<r.getBanca()<<std::endl;
                }
            break;

            case 5:                                                                                                             //Eliminamos un jugador introduciendo su dni
                std::cout<<"Introduzca el DNI del jugador que quiere eliminar"<<std::endl;
                std::cin>>dni;

                if (r.deleteJugador(dni) == 1){
                    std::cout<<"Jugador eliminado con exito"<<std::endl;
                }
                else if (r.deleteJugador(dni) == -1){
                    std::cout<<"La lista esta vacia"<<std::endl;  
                }
                else if(r.deleteJugador(dni) == -2){
                    std::cout<<"Jugador no encontrado"<<std::endl;
                }
            break;

            case 6:                                                                                                             //Se añaden los 3 jugadores por defecto
                std::cout<<"Añadiendo jugadores"<<std::endl;
                r.addJugador(j1);
                r.addJugador(j2);
                r.addJugador(j3);
                std::cout<<"Jugadores añadidos exitosamente"<<std::endl;

            break;

            case 7:                                                                                                             //Salimos del programa
                std::cout<<"Saliendo del programa"<<std::endl;
                std::cout<<"------------------------------------------------------"<<std::endl;

            break;

            default:
                std::cout<<"ERROR, introduzca una opcion valida"<<std::endl;
            break;
        }
    }

    return 0;
}