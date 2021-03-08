#include <iostream>
using namespace std;
bool espar (int v){
	bool res;
	if (v%2==0){//La funcion comprueba si el valor v es par o no
		res=true;
	}
	else{
		res=false;
	}
	return res;
}
int main(){
	int n;
	cout<<"Introduzca un numero para saber si es par o no"<<endl;
	cin>>n;
	if (espar(n)==true){
		cout<<"El numero es par (true)"<<endl;
	}
	else {
		cout<<"El numero no es par (false)"<<endl;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}