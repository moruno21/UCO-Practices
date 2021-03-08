#include <iostream>
using namespace std;
int main(){
	int a;
	cout<<"Introduzca un valor impar"<<endl;
	cin>>a;
	int suma=0;
	if(a%2==1){
		while (a>0){
			suma=suma+a;
			a=a-2;
		}
	cout<<"El resultado es:"<<suma<<endl;
	}
	if(a%2==0){//Si el usuario introduce un numero par a, el programa sumara los numeros impares menores que a, siendo el primero de estos a-1, luego a-3 y asi sucesivamente
		a--;
		while(a>0){
			suma=suma+a;
			a=a-2;
		}
	cout<<"El resultado es:"<<suma<<endl;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
			