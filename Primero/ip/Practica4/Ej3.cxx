#include <iostream>
using namespace std;
int factorial (int v){//En esta funcion realizamos el factorial de cualquier numero que se introduzca
	int i, fact=1;
	for (i=1;i<=v;i++){
		fact=i*fact;
	}
	return fact;
}
int main(){
	int num;
	cout<<"Introduzca un numero para obtener su factorial"<<endl;
	cin>>num;
	cout<<"Su factorial es:"<<factorial (num)<<endl;//Imprimimos la funcion de arriba para el valor num introducido
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}