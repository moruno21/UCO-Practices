#include <iostream>
using namespace std;
int main (){
	int a,b,cont=2;
	cout<<"Introduzca los 5 valores que usted desee"<<endl;
	cin>>a;
	cout<<"Introduzca otro valor"<<endl;
	while (cont<6){
		cin>>b;
		if (a<b){
		cout<<"Introduzca otro valor"<<endl;
		}
		else{
		a=b;
		cout<<"Introduzca otro valor"<<endl;	
		}
		cont++;
	}
cout<<"El menor de los numeros introducidos es:"<<a<<endl;
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}