#include <iostream>
using namespace std;
int main (){
	cout<<"Introduzca la nota de practicas"<<endl;
	float practicas,parcial,examen,media;
	cin>>practicas;
	cin>>parcial;
	cin>>examen;
	media=0.25*practicas+0.25*parcial+0.5*examen;
	cout<<"La media es:"<<media<<endl;
cin.ignore();
cin.get();
}
	
	