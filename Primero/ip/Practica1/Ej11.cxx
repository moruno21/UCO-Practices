#include <iostream>
using namespace std;
int main(){
	int a,b;
	cout<<"Introduzca dos valores enteros"<<endl;
	cin>>a>>b;
	if(a>b){
		cout<<"a="<<b<<"b="<<a<<endl;
	}
	if(a<b){
		cout<<"a="<<a<<"b="<<b<<endl;
	}
cin.ignore();
cin.get();
}