//Archivo contador.cc
//Contiene el cuerpo de las funciones de la clase Contador

#include "contador.h"

Contador::Contador(int valor, int min, int max){                
    if(min>max || valor < min || valor > max){      //Comprobamos que los valores esten bien introducidos, si no lo estan entramos en el if
        valor = 0;
        min = 0;
        max = 1000;
    }
    valor_ = valor;                                 //Asignamos el valor al contador
    min_ = min;                                     //Asignamos el minimo al contador
    max_ = max;                                     //Asignamos el maximo al contador
    lista_.push_back(*this);                        //Guardamos las modificaciones en la lista de contadores
}

void Contador::controlValor(){
    if (valor_>max_){                               //Comprobamos que el valor no exceda el maximo
        valor_=max_;
    }
    else if(valor_<min_){                           //Comprobamos que el valor no exceda el minimo  
        valor_=min_;
    }
    lista_.push_back(*this);                        //Guardamos las modificaciones en la lista de contadores
}

Contador Contador::operator= (const int &n){
    valor_=n;                                       //Asignamos n al valor
    controlValor();
    return *this;
}

Contador Contador::operator=(const Contador &c){
    valor_=c.valor_;                                //Asignamos el valor de c a nuestro contador                        
    min_=c.min_;                                    //Asignamos el minimo de c a nuestro contador 
    max_=c.max_;                                    //Asignamos el maximo de c a nuestro contador 
    controlValor();
    return *this;
}

Contador Contador::operator++(void){
    ++valor_;                                       //Aumentamos el valor del contador
    controlValor();
    return *this;
}

Contador Contador::operator++(int){
    Contador aux = *this;
    ++valor_;                                       //Aumentamos el valor del contador
    controlValor();
    return aux;                                     //Devolvemos el valor del contador que guardamos en aux y aun no estaba aumentado
}

Contador Contador::operator--(void){
    --valor_;                                       //Decrementamos el valor del contador
    controlValor();
    return *this;
}

Contador Contador::operator--(int){
    Contador aux = *this;
    --valor_;                                       //Decrementamos el valor del contador
    controlValor();
    return aux;                                     //Devolvemos el valor del contador que guardamos en aux y aun no estaba decrementado
}

Contador Contador::operator+(const int &n){
    valor_ = valor_ + n;                            //Sumamos valor del contador mas n
    controlValor();
    return *this;
}

Contador operator+(const int &n, const Contador &c){
    Contador aux;
    aux.valor_ = n + c.valor_;                      //Sumamos n mas valor del contador c y lo asignamos al contador aux
    aux.max_ = c.max_;                              //Asignamos el maximo de c al contador aux
    aux.min_ = c.min_;                              //Asignamos el minimo de c al contador aux
    aux.controlValor();
    return aux;
}

Contador Contador::operator-(const int &n){
    valor_ = valor_ - n;                            //Restamos valor del contador mas n
    controlValor();
    return *this;
}

Contador operator-(const int &n, const Contador &c){
    Contador aux;
    aux.valor_ = n - c.valor_;                      //Restamos n mennos valor del contador c y lo asignamos al contador aux
    aux.max_ = c.max_;                              //Asignamos el maximo de c al contador aux
    aux.min_ = c.min_;                              //Asignamos el minimo de c al contador aux
    aux.controlValor();
    return aux;
}

bool Contador::undo(const int &n){
    if (n>= (int)lista_.size() || n<1){             //Si n es mayor que el total de contadores de la lista, o menor que uno, devolvemos false
        return false;
    }
    for(int i=0; i<n; i++){                         //Borramos de la lista los ultimos n elementos
        lista_.pop_back();
    }
    *this = lista_.back();                          //Guardamos en el contador el ultimo valor de la lista
    return true;
}