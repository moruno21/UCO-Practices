#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int digitos (string cad){
	int cont=0;//Variable en la que guardamos el numero de digitos 
	for (int n=0; n<cad.size(); n++){
		if (isdigit(cad[n])){//isdigit nos permite determinar si el elemento de la cadena en el que es o no un digito
			cont++;
		}
	}
	return cont;
}
int main(){
	string cad;
	cout<<"Introduzca una palabra o frase"<<endl;
	getline (cin,cad);
	cout<<"La frase introducida tiene "<<digitos(cad)<<" digito(s)"<<endl;
cin.ignore();
cin.get();
}
