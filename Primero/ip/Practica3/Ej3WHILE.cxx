#include <iostream>
using namespace std;
int main(){
	int num,cont,div;
	cout<<"Introduzca el valor para saber si es primo o no"<<endl;
	cin>>num;
	cont=0;//Esta variable nos indica el numero de divisores que tendra el numero que introduzca el usuario
	div=1;
	while (num>=div){
		if(num%div==0){
		cont++;
		}
	div++;
	}
	if (cont==2){
		cout<<"El numero es primo"<<endl;
	}
	else if (cont>2){
		cout<<"El numero no es primo"<<endl;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}