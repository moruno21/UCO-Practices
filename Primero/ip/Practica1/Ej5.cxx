#include <iostream>
using namespace std;
int main(){
	int x;
	cout<<"Introduzca el numero entero"<<endl;
	cin>>x;
	if(x==0){
		cout<<"El valor es 0"<<endl;
	}
	if(x<0){
		cout<<"El valor es menor que 0"<<endl;
	}
	if(x>0){
		cout<<"El valor es mayor que 0"<<endl;
	}
	cin.ignore();
	cin.get();
}