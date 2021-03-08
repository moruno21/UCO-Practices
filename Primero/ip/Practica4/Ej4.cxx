#include <iostream>
using namespace std;
void divisores (int v){
	int div;
	for(div=1; div<=v; div++){//Empezamos desde 1 para que los divisores aparezcan en orden ascendente (de menor a mayor)
		if (v%div==0){
		cout<<div<<endl;//Cada vez que div sea divisor de un valor v, este se imprimira por pantalla
		}
	}
	}
int main(){
	int a;
	cout<<"Introduzca un numero para obtener sus divisores"<<endl;
	cin>>a;
	cout<<"Sus divisores son:"<<endl;
	divisores (a);//Imprimimos la funcion de arriba para el valor a 
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}


		