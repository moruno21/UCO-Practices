#include <iostream>
#include <string> //fichero de cabecera para cadenas en C++

using namespace std;

int main(void) 
{
string cad1("OM MANI PEME HUNG");
string cad2("recitar este mantra elimina la perturbaciones"
             " \n de la mente llevando al que lo recita a "
             " \n conseguir la paz mental");

cout << "cad1 = " << cad1 << endl
     << "cad1.find(\"EM\") = " << cad1.find("EM") << endl
     << "cad1.rfind(\"E\") = " << cad1.rfind("E") << endl
     << "cad1.find_first_of(\"AEI\") = " << cad1.find_first_of("AEI") << endl
     << "cad1.find_last_of(\"AEI\") = " << cad1.find_last_of("AEI") << endl
     << "cad1.find_first_not_of(\"AEI\") = " << cad1.find_first_not_of("AEI") << endl
     << "cad1.find_last_not_of(\"AEI\") = " << cad1.find_last_not_of("AEI") << endl;

cout << "cad2 = " << cad2 << endl;
cad2.insert(85," REPETIDAS VECES");
cout << "cad2 = " << cad2 << endl;

cad2.erase(59);
cout << "cad2 = " << cad2 << endl;

cad2.replace(54,5,"MENTE");
cout << "cad2 = " << cad2 << endl;


}
