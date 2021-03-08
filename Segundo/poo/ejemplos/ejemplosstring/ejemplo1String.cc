#include <iostream>
#include <string> //fichero de cabecera para cadenas en c++

using namespace std;

int main(void) 
{

string cad1="Ejemplo de uso de cadenas"; 

string cad2, cad3; //No hay inicializador con tama�o para string.

cad2 = " con la clase \"string\" de C++";    //Asignacion
cad3 = cad1 + cad2;    //Concatenacion
cad3+=".";             //Concatenacion

cout << "cad1 = " << cad1 << endl;
cout << "cad2 = " << cad2 << endl;
cout << "cad1 + cad2 = " << cad1 + cad2 << endl; //Concatenacion 
cout << "cad3 = " << cad3 << endl;

cout << "\nLa cadena es: " << cad1
     << "\ncapacidad: " << cad1.capacity()
     << "\ntam. maximo: " << cad1.max_size()
     << "\ntam.: " << cad1.size()
     << "\nlongitud: " << cad1.length()
     << "\nvacia: " << (cad1.empty()?"verdadero\n":"falso\n");

cout << "\nLa cadena es: " << cad2
     << "\ncapacidad: " << cad2.capacity()
     << "\ntam. maximo: " << cad2.max_size()
     << "\ntam.: " << cad2.size()
     << "\nlongitud: " << cad2.length()
     << "\nvacia: " << (cad2.empty()?"verdadero\n":"falso\n");
}
