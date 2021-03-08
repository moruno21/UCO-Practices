#include <iostream>
#include <string>
using namespace std;
int espacios(string cad){
	int cont=0;
	for (int n=0;n<cad.size();n++){
		if (cad[n]==' '){
			cont++;
		}
	}
	return cont;
}
int main(){
	string cad;
	cout<<"Introduzca una frase"<<endl;
	getline (cin,cad);
	cout<<"La frase tiene "<<espacios(cad)<<" espacio(s)"<<endl;
cin.ignore();
cin.get();
}
