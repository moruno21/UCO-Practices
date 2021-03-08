#include <iostream>
using namespace std;
bool esprimo (int v){
	int i, ndiv=0;
	for (i=1;i<=v;i++){
		if ((v%i)==0){
			ndiv++;
		}
	}
	bool res;
	if (ndiv<=2){//Aquí comprobamos el numero de divisores que tiene para saber si es primo o no
		return res=true;
	}
	else{
		return res=false;
	}
}
int main(){
	int a;
	cout<<"Introduzca un numero. Obtendra si el numero es primo (true) o no (false)"<<endl;
	cin>>a;
	if (esprimo(a)==true){
		cout<<"El numero es primo (True)"<<endl;
	}
	else{
		cout<<"El numero no es primo (False)"<<endl;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}




