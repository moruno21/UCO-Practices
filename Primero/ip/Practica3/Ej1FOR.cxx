#include <iostream>
using namespace std;
int main (){
	int a,b,cont;
	cout<<"Introduzca los 5 valores que usted desee"<<endl;
	cin>>a;
	cout<<"Introduzca otro valor"<<endl;
	for (cont=2 ; cont<6 ; cont++){
		cin>>b;
		if (a<b){
		cout<<"Introduzca otro valor"<<endl;
		}
		else{
		a=b;
		cout<<"Introduzca otro valor"<<endl;	
		}
	}
cout<<"El menor de los numeros introducidos es:"<<a<<endl;
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}