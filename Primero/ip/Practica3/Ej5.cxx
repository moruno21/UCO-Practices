#include <iostream>
using namespace std;
int main(){
	int a,b,cont;
	cout<<"Introduzca los valores que desee. El programa funcionara hasta que la media de los numeros indicados sea igual o mayor que 30"<<endl;
	cin>>a;
	cin>>b;
	cont=2;//Cantidad de valores con los que hacemos la media
	while (((a+b)/cont)<30){
		cout<<"Introduzca otro valor"<<endl;
		a=a+b;
		cin>>b;
		cont++;
	}
	cout<<"Fin del programa"<<endl;//Este mensaje aparecera cuando la media de todos los valores introducidos sea mayor o igual que 30
cin.ignore();
cin.get();
}
