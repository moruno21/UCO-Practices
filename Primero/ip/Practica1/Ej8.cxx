#include <iostream>
using namespace std;
int main(){
	float a,b,c;
	cout<<"Introduzca los 3 valores"<<endl;
	cin>>a;
	cin>>b;
	cin>>c;
	if((a>b)&&(a>c)){
		cout<<"El mayor valor es:"<<a<<endl;
	}
	if((b>a)&&(b>c)){
		cout<<"El mayor valor es:"<<b<<endl;
	}
	if((c>a)&&(c>b)){
		cout<<"El mayor valor es:"<<c<<endl;
	}
	else if((a=b)&&(b=c)){
		cout<<"El mayor valor es:"<<a<<endl;
	}
cin.ignore();
cin.get();
}