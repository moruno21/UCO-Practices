//programa que pedira constantemente valores al usuario hasta que la media sea 30

#include <iostream>

using namespace std;

int main(){
	int a, n=1, suma=0;
	cout<<"Introduzca valores"<<endl;
	cin>>a;
	
	suma=suma+a;
	int media=suma/n;

	if (media>=30){
		cout<<"Error"<<endl;
		return 0;
	}

	while (media<30){
		cin>>a;
		n++;
		suma=suma+a;
		media=suma/n;
		if (media>=30){
			cout<<"Error"<<endl;
		}
	}
	
return 0;
}