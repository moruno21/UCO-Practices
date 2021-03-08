#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int vocales (string cad){
	int cont=0;//Variable donde guardamos el total de mayusculas que tiene la cadena
	for (int i=0; i<cad.size(); i++){
		char c=cad[i];
		cad[i]=tolower(c);//Pasamos todas las letras a mayuscula para no tener que buscar tambien vocales en mayuscula
		if ((cad[i]=='a')||(cad[i]=='e')||(cad[i]=='i')||(cad[i]=='o')||(cad[i]=='u')){
			cont++;
		}
	}
	return cont;
}
int main(){
	string cad;
	cout<<"Introduzca una palabra o frase"<<endl;
	getline (cin, cad);
	cout<<"La frase introducida tiene "<<vocales(cad)<<" vocal(es)"<<endl;
cin.ignore();
cin.get();
}