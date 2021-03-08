#include <iostream>
using namespace std;
int main(){
	int a,b;
	cout<<"Introduzca el numero para mostrar sus divisores de mayor a menor"<<endl;
	cin>>a;
	b=a;//Esto es para mostrar los divisores de a de forma descendente (de mayor a menor)
	cout<<"Sus divisores son:"<<endl;
	while (b>0){
		if (a%b==0){
			cout<<b<<endl;
		}
		b--;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}