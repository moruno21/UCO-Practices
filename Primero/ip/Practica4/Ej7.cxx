#include <iostream>
using namespace std;
int Ndivisores (int v){
	int b, cont=0;
	if (v>0){//Esto es si el numero introducido es positivo
		for (b=1; b<=v; b++){
			if (v%b==0){
			cont++;
			}
		}
		cout<<cont<<endl;//Imprime por pantalla el total de divisores del numero introducido
	}
	if (v==0){//Si el numero introducido es 0, no tiene divisores
		cout<<"El numero no tiene divisores"<<endl;
	}
	if (v<0){//Esto es si el numero introducido es negativo
		for (b=-1; b>=v; b--){
			if (v%b==0){
			cont++;
			}
		}
		cout<<cont<<endl;//Imprime por pantalla el total de divisores del numero introducido
	}
	
}
int main(){
	int num;
	cout<<"Introduzca un numero para saber cuantos divisores tiene"<<endl;
	cin>>num;
	cout<<"Los divisores totales del numero son:"<<endl;
	Ndivisores (num);
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
	
			
			