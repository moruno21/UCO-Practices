#include <iostream>
using namespace std;
int main(){
	int num,div;
	cout<<"Introduzca un numero para obtener sus divisores en orden ascendente"<<endl;
	cin>>num;
	cout<<"Los divisores son:"<<endl;
	for ((div=1);(num>=div);(div++)){
		if (num%div==0){
			cout<<div<<endl;
		}
	}
cout<<"Fin de programa"<<endl;
cin.ignore();
cin.get();
}