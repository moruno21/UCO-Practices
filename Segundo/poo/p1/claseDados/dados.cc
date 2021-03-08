//Archivo dados.cc
//Contiene el cuerpo de las funciones de la clase Dados

#include "dados.h"

Dados::Dados(){         //Constructor de la clase Dados       
    srand(time(NULL));
    d1_=1;              //Puesta del dado 1 a 1
    d2_=1;              //Puesta del dado 2 a 1
    
    lanz1_=0;           //Puesta a 0 de los lanzamientos del dado 1
    lanz2_=0;           //Puesta a 0 de los lanzamientos del dado 2

    sum1_=0;            //Puesta a 0 de la suma de valores del dado 1
    sum2_=0;            //Puesta a 0 de la suma de valores del dado 2
}

void Dados::lanzamiento(){              //Función de lanzamiento de dados aleatorio 
    d1_=(rand()%6)+1;                   //Lanzamiento dado 1
    d2_=(rand()%6)+1;                   //Lanzamiento dado 2

    lanz1_++;                           //Aumentamos en 1 los lanzamientos realizados del dado 1
    lanz2_++;                           //Aumentamos en 1 los lanzamientos realizados del dado 2

    sum1_ += d1_;                       //Sumamos el dado 1 al sumatorio de valores del dado 1
    sum2_ += d2_;                       //Sumamos el dado 2 al sumatorio de valores del dado 2

    for (int i=4; i>=0; i--){           //Bucle que guarda el valor del dado obtenido en el vector con los ultimos 5 valores del dado 1
        ultimos1 [i] = ultimos1 [i-1];  //Corre los valores que hay en el vector una posición hacia la derecha, dejando la primera posición para el dado que se acaba de obtener
    }
    ultimos1 [0] = d1_;                 //Guarda el valor obtenido en la primera posición del vector

    for (int i=4; i>=0; i--){           //Bucle que guarda el valor del dado obtenido en el vector con los ultimos 5 valores del dado 2
        ultimos2 [i] = ultimos2 [i-1];  //Corre los valores que hay en el vector una posición hacia la derecha, dejando la primera posición para el dado que se acaba de obtener
    }
    ultimos2 [0] = d2_;                 //Guarda el valor obtenido en la primera posición del vector

}

bool Dados::setDado1(const int &n){             //Funcion que cambia el valor del dado 1
    if (n>=1 && n<=6){
        d1_=n;                                  //Asignamos al dado 1 el valor n
        lanz1_++;                               //Aumentamos en 1 los lanzamientos realizados del dado 1
        sum1_ += d1_;                           //Sumamos el dado 1 al sumatorio de valores del dado 1
            
        for (int i=4; i>=0; i--){               //Bucle que guarda el valor del dado obtenido en el vector con los ultimos 5 valores del dado 1
            ultimos1 [i] = ultimos1 [i-1];      //Corre los valores que hay en el vector una posición hacia la derecha, dejando la primera posición para el dado que se acaba de obtener
        }
        ultimos1 [0] = d1_;                     //Guarda el valor obtenido en la primera posición del vector
        return true;                            //Retornará true si se acaba asignando el dado correctamente
    }
    return false;                               //Retornará false si no entramos en el if, es decir, si el valor que intentamos asignar no es correcto
}

bool Dados::setDado2(const int &n){             //Funcion que cambia el valor del dado 2
    if (n>=1 && n<=6){
        d2_ = n;                                //Asignamos al dado 2 el valor n
        lanz2_++;                               //Aumentamos en 1 los lanzamientos realizados del dado 2
        sum2_+= d2_;                            //Sumamos el dado 2 al sumatorio de valores del dado 2

        for (int i=4; i>=0; i--){               //Bucle que guarda el valor del dado obtenido en el vector con los ultimos 5 valores del dado 2
            ultimos2 [i] = ultimos2 [i-1];      //Corre los valores que hay en el vector una posición hacia la derecha, dejando la primera posición para el dado que se acaba de obtener
        }
        ultimos2 [0] = d2_;                     //Guarda el valor obtenido en la primera posición del vector
        return true;                            //Retornará true si se acaba asignando el dado correctamente
    }
    return false;                               //Retornará false si no entramos en el if, es decir, si el valor que intentamos asignar no es correcto
}


float Dados::getMedia1()const{          //Funcion que calcula la media de los valores obtenidos para el dado 1
    if (lanz1_ == 0){
        return 0;                       //Si no hemos lanzado el dado 1, la media será 0
    }
    return (float)sum1_/lanz1_;         //Hacemos casting a float para obtener un valor decimal y no entero (en el caso en el que la media sea decimal)
}

float Dados::getMedia2()const{          //Funcion que calcula la media de los valores obtenidos para el dado 2
    if (lanz2_ == 0){
        return 0;                       //Si no hemos lanzado el dado 2, la media será 0
    }
    return (float)sum2_/lanz2_;         //Hacemos casting a float para obtener un valor decimal y no entero (en el caso en el que la media sea decimal)
}

void Dados::getUltimos1(int v[5]){      //Funcion en la que se copia en un vector los ultimos 5 valores del dado 1
    for (int i=0; i<5; i++){
        v[i]=ultimos1[i];
    }
}

void Dados::getUltimos2(int v[5]){      //Funcion en la que se copia en un vector los ultimos 5 valores del dado 2
    for (int i=0; i<5; i++){
        v[i]=ultimos2[i];
    }
}







