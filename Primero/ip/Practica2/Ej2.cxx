#include <iostream>
using namespace std;
int main(){
	int num;
	cout<<"Introduzca un valor"<<endl;
	cin>>num;
	int suma=0;
	while (num>0){
		if(num>0){
			suma=suma+num;
			num=num-1;
		}
	}
cout<<"El resultado es:"<<suma<<endl;
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
		
		