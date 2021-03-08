#include <iostream>
using namespace std;
int combinaciones (int n, int k){
	int factn=1, factk=1, factresta=1;
	if (n==0){//Si n es 0, su factorial es 1
		factn=1;
	}
	else {
		for (int i=1;i<=n;i++){//Calculamos el factorial de n
			factn=i*factn;
		}
	}
	if (k==0){//Si k es 0, su factorial es 1
		factk=1;
	}
	else {//Calculamos el factorial de n
		for (int o=1;o<=k;o++){
			factk=o*factk;
		}
	}
	int resta=n-k;
	for (int u=1;u<=resta;u++){//Calculamos el factorial de la resta
			factresta=u*factresta;
		}
	
	return ((factn)/((factk)*(factresta)));//Esta es la operacion que se realiza cuando queremos calcular un numero combinatorio
}
int main(){
	int a,b;
	cout<<"Introduzca dos valores para calcular el numero combinatorio (Ejemplo: 5 sobre 4)"<<endl;
	cin>>a;
	cin>>b;
	cout<<"El resultado de "<<a<<" sobre "<<b<<" es: "<<combinaciones (a,b)<<endl;
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
	
		