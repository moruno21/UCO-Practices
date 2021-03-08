//Archivo ruleta.cc
//Contiene el cuerpo de las funciones de la clase Ruleta
//En algunas funciones, se utiliza para iterar en una lista el tipo de variable auto, que equivaldria (en nuestro caso) a poner:
//std::list<Jugador>::iterator i == auto i

#include "ruleta.h"
#include <fstream>
#include <ctime>


bool Ruleta::setBanca(int const &banca){    //Función modificadora del valor de banca
    if (banca<0){                           //No se puede asignar valores negativos a la banca
        return false;
    }
    banca_=banca;
    return true;
}


bool Ruleta::setBola(int const &bola){      //Función modificadora del valor de bola
    if (bola<0 || bola>36){                 //Si la bola no esta en el rango 0-36, devolvera false
        return false;
    }
    bola_=bola;                             //Si la bola esta en el rango 0-36, se asignara correctamente y devolvera true
    return true;
}


bool Ruleta::addJugador(Jugador const &jugador){                                            //Función que añade un jugador a la lista
    for (std::list<Jugador>::iterator i = jugadores_.begin(); i != jugadores_.end(); i++){  //Recorremos la lista para buscar si ya existe el jugador que queremos añadir, para asi devolver false
        if(i->getDNI()==jugador.getDNI()){
            return false;
        }
    }
    jugadores_.push_back(jugador);                                                          //Si no hemos encontrado el jugador en la lista, lo añadimos a la lista
    std::fstream f;
    std::string nombrefichero= jugador.getDNI() + ".txt";
    
    f.open(nombrefichero, std::ios_base::app);
    f.close();
    return true;
}


int Ruleta::deleteJugador(std::string const &dni){                                          //Función que borra a un jugador de la lista pasando un dni como parámetro
    if(jugadores_.empty()) return -1;                                                       //Se devuelve -1 si la lista esta vacia

    for (std::list<Jugador>::iterator i = jugadores_.begin(); i != jugadores_.end(); i++){  //Recorremos la lista para buscar si ya existe el jugador que queremos eliminar
        if(i->getDNI()==dni){
            jugadores_.erase(i);                                                            //Eliminamos el jugador
            return 1;
        }
    }
    return -2;                                                                              //Se devuelve -2 si no hemos encontrado al jugador que queremos borrar
}


int Ruleta::deleteJugador(Jugador const &jugador){                              //Función que borra a un jugador de la lista pasando un objeto del tipo Jugador como parámetro
    if(jugadores_.empty()) return -1;                                           //Se devuelve -1 si la lista esta vacia

    for (auto i=jugadores_.begin(); i!=jugadores_.end(); i++){                  //Recorremos la lista para buscar si ya existe el jugador que queremos eliminar
        if(i->getDNI()==jugador.getDNI()){
            jugadores_.erase(i);                                                //Eliminamos el jugador
            return 1;
        }
    }
    return -2;                                                                  //Se devuelve -2 si no hemos encontrado al jugador que queremos borrar
}


void Ruleta::escribeJugadores(){                                    //Funcion que escribe los datos de la lista de jugadores en un fichero
    std::fstream f;
    f.open("jugadores.txt", std::ios::out);
    for (auto i= jugadores_.begin(); i!=jugadores_.end(); i++){     //Cada vez que entremos en el bucle, estaremos en un jugador distinto, del cual se iran escribiendo sus datos en el fichero separados por comas
        f<<i->getDNI()<<","<<
        i->getCodigo()<<","<<
        i->getNombre()<<","<<
        i->getApellidos()<<","<<
        i->getDireccion()<<","<<
        i->getLocalidad()<<","<<
        i->getProvincia()<<","<<
        i->getPais()<<","<<
        i->getDinero()<<","<<std::endl;
    }
    f.close();
}


void Ruleta::leeJugadores(){                                                                                    //Funcion que escribe los datos de un fichero en la lista jugadores
    jugadores_.empty();                                                                                         //Al comienzo, vaciamos la lista de jugadores
    std::fstream f;
    f.open("jugadores.txt", std::ios::in);
    
    char dni[255], codigo[255], nombre[255], apellidos[255]; 
    char direccion[255], localidad[255], provincia[255], pais[255], dinero[255];                                //Creamos variables para almacenar temporalmente los datos del jugador
    
    while(f.getline(dni, 255, ',')){
            
        f.getline(codigo, 255, ',');
        f.getline(nombre, 255, ',');
        f.getline(apellidos, 255, ',');
        f.getline(direccion, 255, ',');
        f.getline(localidad, 255, ',');
        f.getline(provincia, 255, ',');
        f.getline(pais, 255, ',');
        f.getline(dinero, 255, '\n');

        Jugador aux (dni, codigo, nombre, apellidos, 0, direccion, localidad, provincia, pais, atoi(dinero));   //Creamos un jugador aux y le pasamos sus datos
        jugadores_.push_back(aux);                                                                              //Pasamos aux a la lista
    }
    f.close();
}


void Ruleta::getPremios(){                                                              //Funcion que actualiza el dinero ganado o perdido por los jugadores
    for (auto i=jugadores_.begin(); i!=jugadores_.end(); i++){
        i->setApuestas();                                                               //Se hacen las apuestas
        std::list<Apuesta> aux = i->getApuestas();                                      //Se guardan las apuestas en una lista auxiliar
        for (auto j=aux.begin(); j!=aux.end(); j++){
            Apuesta apuesta= *j;
            switch(apuesta.tipo){                                                       //Segun el tipo de apuesta, entraremos en un caso del switch o en otro
                
                case 1:                                                                 //Apuesta sencilla
                    if (bola_ == stoi(apuesta.valor)){                                  //Si sale el numero de la bola que habia apostado el jugador, gana el jugador y pierde la banca
                        setBanca(getBanca() - 35*apuesta.cantidad);                     
                        i->setDinero(i->getDinero() + (apuesta.cantidad*35));           
                    }
                    else{                                                               //Si no sale el numero de la bola que habia apostado el jugador, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);                        
                        i->setDinero(i->getDinero() - apuesta.cantidad);                             
                    }
                break;

                case 2:                                                                                                     //Apuesta rojo o negro
                    if (bola_==0){                                                                                          //Si la bola que sale es 0, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);
                    }

                    else if ((apuesta.valor=="rojo"&& esRoja(bola_)) || (apuesta.valor=="negro" && !esRoja(bola_))){        //Si el color de la bola coincide con el color apostado, gana el jugador y pierde la banca
                        setBanca(getBanca() - apuesta.cantidad);
                        i->setDinero(i->getDinero()+(apuesta.cantidad));
                    }

                    else{                                                                                                   //Si el color de la bola no coincide con el color apostado, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);
                    }

                break;

                case 3:                                                                                                     //Apuesta par o impar
                    if (bola_==0){                                                                                          //Si la bola que sale es 0, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);
                    }
                    else if ( (apuesta.valor=="par"&& esPar(bola_)) || (apuesta.valor=="impar" && !esPar(bola_))){          //Si la paridad de la bola coincide con la apostada, gana el jugador y pierde la banca
                        setBanca(getBanca() - apuesta.cantidad);
                        i->setDinero(i->getDinero()+(apuesta.cantidad));
                    }

                    
                    else{                                                                                                   //Si la paridad de la bola no coincide con la apostada, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);

                    }
                break;

                case 4:                                                                                                     //Apuesta alto o bajo                                                                 
                    if (bola_==0){                                                                                          //Si la bola que sale es 0, gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);
                    }

                    else if ( (apuesta.valor=="alto"&& esAlta(bola_)) || (apuesta.valor=="bajo" && !esAlta(bola_))){        //Si la bola y la apuesta son ambas alta o ambas baja, gana el jugador y pierde la banca
                        setBanca(getBanca() - apuesta.cantidad);
                        i->setDinero(i->getDinero()+(apuesta.cantidad));
                    }

                    else{                                                                                                   //Si la bola y la apuesta son una alta y una baja (o viceveersa), gana la banca y pierde el jugador
                        setBanca(getBanca() + apuesta.cantidad);
                        i->setDinero(i->getDinero() - apuesta.cantidad);
                        
                    }
                break;
            }
        }
    }
}


bool Ruleta::esRoja(int const &valor){      //Funcion que determina si la bola es roja o no
    int rojos[18] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
        for(int i=0; i<18; i++){
            if(valor == rojos[i]){
                return true;                //Si es roja devolvera true
            }
        }
    return false;                           //Si es negra devolvera false
}


bool Ruleta::esPar(int const &valor){       //Funcion que determina si la bola es par o no              
    if (valor%2==0){
        return true;                        //Si es par devolvera true
    }
    return false;                           //Si es impar devolvera false
}


bool Ruleta::esAlta(int const &valor){      //Funcion que determina si la bola es un valor alto o no
    if (valor>=1 && valor<=18){
        return false;                       //Si esta entre 1 y 18 devolvera false
    }
    return true;                            //Si esta entre 19 y 36 devolvera false
}