//Archivo ns.cc
//Programa que muestra el uso de los espacios de nombre namespace

#include <iostream>
using namespace std;

namespace n1{
    int a;
    int b;
}

namespace n2{
    int a;
    int c;
}

int main(void){

    int a = 55;
    n1::a = 0;
    n2::a = 2; 
    cout << "a =  " << a << "\n"; 
    cout << "n1::a =  " << n1::a << "\n"; 
    cout << "n2::a =  " << n2::a << "\n"; 

}