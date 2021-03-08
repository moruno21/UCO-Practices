#include <iostream>
using namespace std;
int main(){
	float a, suma=0,cont=0;
	cout<<"Introduzca numeros para realizar su media"<<endl;
	cin>>a;
	while (a>0){
		suma=suma+a;
		cin>>a;
		cont++;
	}
	float media=suma/cont;
	cout<<"La media es "<<media<<endl;
cin.get();
cin.ignore();
}