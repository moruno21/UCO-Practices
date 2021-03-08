#include <iostream>
using namespace std;
int main(){
	int num,div;
	cout<<"Introduzca un numero para obtener sus divisores en orden ascendente"<<endl;
	cin>>num;
	div=1;
	cout<<"Los divisores son:"<<endl;
	while (num>=div){
		if (num%div==0){
			cout<<div<<endl;
		}
	div++;
	}
cout<<"Fin de programa"<<endl;
cin.ignore();
cin.get();
}