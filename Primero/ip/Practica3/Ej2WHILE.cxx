#include <iostream>
using namespace std;
int main(){
	float a,b;
	cout<<"Introduzca los valores positivos que desee. En el momento en el que introduzca un valor menor que 0, el programa finalizara indicandole el mayor de los numeros introducidos"<<endl;
	cin>>a;
	cout<<"Introduzca otro valor"<<endl;
	cin>>b;
	if ((a<0)||(b<0)){
		if (a>b){
			cout<<"El numero mayor es:"<<a<<endl;
		}
		else{
			if(a<b){
				cout<<"El numero mayor es:"<<b<<endl;
			}
			else{
				cout<<"El mayor valor es:"<<a<<endl;
			}
		}
	}
	else{
		while ((a>=0)&&(b>=0)){
			if (a>b){
			b=a;//Guardamos siempre el mayor de los valores en b
			}
			cout<<"Introduzca otro valor"<<endl;
			cin>>a;
		}
		cout<<"El mayor numero es:"<<b<<endl;//Como siempre hemos ido guardando el mayor de los valores en , al final imprimimos ese numero
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
			
		