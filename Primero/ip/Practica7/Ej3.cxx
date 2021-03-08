#include <iostream>
#include <string>
using namespace std;
void convierte_a_mayuscula (string &cad){
	for (int n=0; n<cad.size(); n++){
		char c= cad[n];//Guardamos el valor del elemento de la cadena en el que nos encontremos en la variable c para poder pasarlo despues a mayuscula
		cad[n]= toupper(c);//mediante toupper transformamos el caracter que estemos analizando en mayuscula
	}
}
int main(){
	string cad;
	cout<<"Introduzca una palabra o frase para ser pasada a mayuscula"<<endl;
	getline (cin,cad);
	convierte_a_mayuscula (cad);
	cout<<cad<<endl;
cin.ignore();
cin.get();
}