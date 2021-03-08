//Programa que pasa un ángulo de grados a radianes
#include <iostream>
using namespace std;
int main(){
	float grados,radianes;
	cout<<"Introduzca el valor del angulo en grados"<<endl;
	cin>>grados;
	radianes=grados*3.1415/180;
	cout<<"El resultado es:"<<radianes<<endl;
	cin.ignore();
	cin.get();
}