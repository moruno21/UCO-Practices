#include <iostream>
using namespace std;
bool esprimo (int n){
	bool res;
	int ndiv=0, i;
	if (n>0){
		for (i=1;i<=n;i++){
			if (n%i==0){
				ndiv++;//Empezamos a contar cuantos divisores tiene el numero
			}
		}
		if (ndiv==1||ndiv==2){
			return res=true;
		}
		else{
			return res=false;
		}
	}
	else{
		for (i=-1;i>=n;i--){
			if (n%i==0){
				ndiv++;
			}
		}
		if (ndiv==2){
			return res=true;
		}
		else{
			return res=false;
		}
	}
}
void primos (int h){
	int d,e=0;
	for (d=1; e!=h; d++){
		if (esprimo (d)==true){
			cout<<d<<endl;
			e++;
		}
	}
	}
int main(){
	int num;
	cout<<"Introduzca un numero"<<endl;
	cin>>num;
	cout<<"Los primeros "<<num<<" numeros primos son:"<<endl;
	primos (num);
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}