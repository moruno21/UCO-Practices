//Programa que realiza la raiz cuadrada de un numero introducido por el usuario

#include <iostream>
#include <cmath>//incluye la libreria matematica
using namespace std;
int main(){
	float x;
	cout<<"Introduza el número"<<endl;
	float raiz_x=sqrt(x);
	cin>>x;
	if(x>=0){
		cout<<"El resultado es :"<<sqrt(x)<<endl;
	}
	else {
		cout<<"Error"<<endl;
	}
	cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();

}
	
