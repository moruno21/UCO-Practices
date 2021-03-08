#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 
float trace(float m[4] [4]){
float suma=0;
int i;
	for (i=0; i<4; i++){
		suma=suma+m[i] [i];//Suma solo los elementos de la diagonal de la matriz
	}
return suma;//Devuelve el valor de la traza
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
	assert( trace(m)== 10 );
	return 0;
}	


