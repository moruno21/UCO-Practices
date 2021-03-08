//Programa que calcula el area de una circunferencia dado el radio
#include <iostream>
using namespace std;
int main(){
	float area,radio;
	cout<<"Introduzca el valor del radio"<<endl;
	cin>>radio;
	area=radio*radio*3.1415;
	cout<<"El area es:"<<area<<endl;
	cin.ignore();
	cin.get();
}