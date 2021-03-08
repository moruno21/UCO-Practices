#include <iostream>
#include <string>
using namespace std;
bool palindromo (string cad){
	for (int i=0; i<cad.size()/2; i++){//Comprobamos solo hasta la mitad de la cadena ya que avazamos tanto por el principio como por el final, siendo inutil comprobar de nuevo algo ya comprobado
		if (cad[i]!=cad[cad.size()-1-i]){
			return false;
		}
	}
	return true;//Solo seras un palindromo si no se ha entrado ni una sola vez en el if anterior
}
int main(){
	string cad;
	cout<<"Introduzca una palabra pa saber si es un palindromo o no"<<endl;
	getline (cin,cad);
	if (palindromo(cad)==true){
		cout<<"Es palindromo"<<endl;
	}
	else{
		cout<<"No es palindromo"<<endl;
	}
cin.ignore();
cin.get();
}