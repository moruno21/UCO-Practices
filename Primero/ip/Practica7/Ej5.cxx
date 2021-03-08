#include <iostream>
#include <string>
using namespace std;
void replace (string &cad, char a, char b){
	for (int i=0; i<cad.size(); i++){
		char c=cad[i];
		if (c==a){//Si el valor c de la cadena es igual al valor que queremos cambiar, entramos en el if
			cad[i]=b;//Cambiamos el valor de la cadena por el que el usuario desee
		}
	}
}
int main(){
	char a,b;
	string cad;
	cout<<"Introduzca el texto que usted desee"<<endl;
	getline(cin,cad);
	cout<<"Introduzca primero la letra que quiere cambiar, y despues la letra por la cual esta sera sustituida"<<endl;
	cin>>a>>b;
	replace (cad,a,b);
	cout<<cad<<endl;
cin.ignore();
cin.get();
}
