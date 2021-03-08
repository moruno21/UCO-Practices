#include <iostream>
using namespace std;
bool esperfecto (int v){
	int div=1,i;
	for (i=0;div<v;div++){//Entramos en el while hasta que el divisor alcance el valor del numero introducido
		if (v%div==0){
			i=i+div;
		}
	}
	if (i==v){//Aqui se compara el numero introducido (v) con la suma de sus divisores (i)
	return true;//Solo sera perfecto si el valor introducido coincide con la suma de sus divisores
	}
	else{//En todos los demas casos, el numero no sera perfecto
	return false;
	}
}
int main(){
	int num;
	cout<<"Introduzca un numero para saber si es perfecto o no (la suma de sus divisores es igual al propio numero)"<<endl;
	cin>>num;
	if (esperfecto (num)==true){
		cout<<"El numero es perfecto"<<endl;
	}
	if (esperfecto (num)==false){
		cout<<"El numero no es perfecto"<<endl;
	}
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}

		