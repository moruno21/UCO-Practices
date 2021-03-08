#include <iostream>
#include <string> //fichero de cabecera para cadenas en C++

using namespace std;

int main(void) 
{
string cad1(8,'x');
string cad2("0123456789"); //igual que string cad2="0123456789";
string nombre1, nombre2;

cout << cad1;
cout << endl;

cout << "introduce nombre 1: ";
cin >> nombre1;
cout << "introduce nombre 2: ";
cin >> nombre2;

//Comparacion de cadenas
if (nombre1>nombre2) cout << nombre1 << " > " << nombre2;
else if (nombre1<nombre2) cout << nombre1 << " < " << nombre2;
     else cout << nombre1 << " = " << nombre2;
cout << endl;

//Subcadenas
cad1=cad2.substr(5,3);
cout << "cadena = " << cad2 << endl;
cout << "subcadena = " << cad1;
cout << endl;

//Intercambio de cadenas
cad1.swap(cad2);
cout << "cad1 = " << cad2 << endl;
cout << "cad2 = " << cad1;
cout << endl;

}
