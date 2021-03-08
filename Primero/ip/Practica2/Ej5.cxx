#include <iostream>
using namespace std;
int main(){
	int a, b;
	cout<<"Introduce un numero cualquiera para mostrar sus divisores de menor a mayor"<<endl;
	cin>>a;
	b=1;//Esto es para mostrar los numeros en orden ascendente (de menor a mayor)
	cout<<"Los numeros divisores son:"<<endl;
	while(a>=b){
		if(a%b==0){		
		cout<<b<<endl;//b se mostrara tantas veces como este sea divisor de a
		}
		b++;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}