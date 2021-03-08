#include <iostream>
#include <string> //fichero de cabecera para cadenas en C++

using namespace std;

int main(void) 
{
string cad;
string may, min;

cout << "Introduce otra cadena con espacios en blanco: ";
getline(cin,cad);

cout << "\nLa cadena es: " << cad
     << "\ncapacidad: " << cad.capacity()
     << "\ntam. maximo: " << cad.max_size()
     << "\ntam.: " << cad.size()
     << "\nlongitud: " << cad.length()
     << "\nvacia: " << (cad.empty()?"verdadero\n":"falso\n");

cout << "may/min: \n";

for(int i = 0; i < cad.length(); i++)
    may+=toupper(cad[i]); // el acceso con at() es más seguro
cout << endl;

for(int i = 0; i < cad.length(); i++)
    min+=tolower(cad[i]);
cout << may << endl;
cout << min << endl;
}
