#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
void fijaValorAleatorio (int v[], int n, int max){
	int secs=time(0);
	srand(secs);
	for (int i=0; i<n; i++){
		v[i]=rand()%(max+1);
	}
}
int main(){
	cout<<"Introduzca el numero maximo para sus valores aleatorios"<<endl;
	int max; cin>>max;
	int v[5];
	fijaValorAleatorio (v,5,max);
cin.ignore();
cin.get();
}