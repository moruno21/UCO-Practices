#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std; 
int find(int val, int v[], int n){
	int cont=0;
	for (int i=0; i<n; i++){
		if (v[i]==val){
			cont++;//Aumentaremos la variable cont de 1 en 1 cada vez que aparezca el valor val en el vector
		}
	}
return cont;//Devolvemos el total de veces que aparece val en el vector
}
int test();
int main(){ 
		int nerrors=test();
		if (nerrors==0){
			cout<<"Correcto "<<endl;
		}
		else{
			cout<<"Hay "<<nerrors<<" errores en el test"<<endl;
		}
		system("pause");
cin.ignore();
cin.get();
}

int test(){
	int errors=0;
	//llama a la funcion para el valor 10 
	int v1[10]={1,2,2,3,1,2,2,3,4,5};//crea el vector
	if ( find(1,v1,10)!=2) errors++;
	if ( find(10,v1,10)!=0) errors++;
	if ( find(2,v1,10)!=4) errors++;
	if ( find(-1,v1,10)!=0) errors++;
	 
 return errors;
}	


