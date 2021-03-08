#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 
int find(float m[4] [4], float val){
int cont=0;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if (m[i] [j]==val){
				cont++;//Cada vez que el elemento de la matriz que estemos evaluando sea igual que val, sumaremos uno a cont
			}
		}
	}
return cont;//Retorna el numero de veces que aparece val en la matriz
}

int test();//indica que la funcion test esta mas abajo
int main(){ 
		test();
		cout<<"Correcto"<<endl;
		system("pause");
		return 0;

}
//funcion de test
int test(){
	
	float m[4][4]={ {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
	assert(  find(m,1 )==4);
	assert(  find(m,2 )==4);
	assert(  find(m,-1 )==0);
	return 0;
}	


