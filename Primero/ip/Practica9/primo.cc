#include <iostream>
using namespace std;
int main(){
	int n,div,cont=0;
	cout<<"Introduzca el numero"<<endl;
	cin>>n;
	div=1;
	while(div<=n){
		if (n%div==0){
		cont++;
		}
		div++;
	}
	if (cont==2){
		cout<<"El numero es primo"<<endl;
	}
	else{
		cout<<"El numero no es primo"<<endl;
	}

return 0;
}