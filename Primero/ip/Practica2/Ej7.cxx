#include <iostream>
using namespace std;
int main(){
	int a,b,cont=0;
	cout<<"Introduzca un nuMero cualquiera"<<endl;
	cin>>a;
	b=1;
	while (a>=b){
		if (a%b==0){
		cont++;
		}
		b++;
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
