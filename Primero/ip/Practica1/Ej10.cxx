#include <iostream>
using namespace std;
int main(){
	float num;
	int prueba;
	cout<<"Introduzca el numero entero"<<endl;
	cin>>num;
	prueba=num/2;
	if (prueba==(num/2)){
		cout<<"El valor es par"<<endl;
	}
	else{
		cout<<"El valor es impar"<<endl;
	}
cin.ignore();
cin.get();
}