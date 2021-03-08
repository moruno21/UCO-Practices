#include <iostream>
using namespace std;
int main(){
	int a;
	cout<<"Introduzca un valor"<<endl;
	cin>>a;
	int cont=1;
	int suma=0;
	while (cont<=a){
		if ((cont%2==0)||(cont%3==0)){//Entraremos en la if con que solo una de las condiciones de cumplan
			suma=suma+cont;
		}
	cont++;//Empezamos desde 1 hasta que lleguemos al valor de a (incluyendo a)
	}
	cout<<"El resultado de la suma es:"<<suma<<endl;
cin.ignore();
cin.get();
}
			