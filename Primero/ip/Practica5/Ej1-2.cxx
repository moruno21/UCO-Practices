#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
void lee (float v1[], int n){
	int v;
	cout<<"Introduzca los 10 elementos del vector"<<endl;
	for (int i=0; i<n; i++){
		int a;
		cin>>a;
		v1[i]=a;
	}
}
void imprime (float v1[], int n){
	cout<<"Los valores de su vector son:"<<endl;
	for (int i=0; i<n; i++){
		cout<<v1[i]<<endl;
	}
}
int main(){
	float v[10];
	lee (v,10);
	imprime (v,10);
cin.ignore();
cin.get();
}