//Programa que comprueba si los numeros introducidos son amigos

#include <iostream>

using namespace std;

int main(){
	int a,b;
	cout<<"Introduzca dos numeros para comprobar si son amigos: "<<endl;
	cin>>a;
	cin>>b;
	int sumada=0,sumadb=0;
	int diva=1, divb=1;
	
	while (diva<a){
		if (a%diva==0){
		sumada=sumada+diva;
		}
	diva++;
	}
	
	while (divb<b){
		if (b%divb==0){
		sumadb=sumadb+divb;
		}
	divb++;
	}
	
	if ((sumada==b)&&(sumadb==a)){
		cout<<"Los numeros son amigos"<<endl;
	}
	else{
		cout<<"Los numeros no son amigos"<<endl;
	}
	
return 0;
}