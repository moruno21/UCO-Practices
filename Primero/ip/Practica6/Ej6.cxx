#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 
void max_row(float m[4] [4], float max[4]){
int i,j;
	int mayor;
	for (i=0; i<4; i++){
		mayor=m[i] [0];
		for (j=0; j<4; j++){
			if (m[i] [j]>mayor){
				mayor=m[i] [j];//Comprueba uno por uno cual es el mayor elemento de cada fila
			}
		}
		max[i]=mayor;//Acaba guardando en el vector max el mayor elemento de cada fila
	}
}
		
int test();//indica que la funcion test esta mas abajo
int main(){ 
		test();
		cout<<"Correcto"<<endl;
		system("pause");
		return 0;
}
//funcion de test
bool iguales(float m[4],float m2[4]){
		for(int i=0;i<4;i++)
				if (m[i]!=m2[i]) return false;
		return true;
}
int test(){
	
	float m[4][4]={ {1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	float max[4];
	float max_res[4]={1,2,3,4};
	max_row(m,max);
	assert(iguales(max,max_res));

	float m2[4][4]={ {-1,5,1,1},{5,1,4,8},{2,3,-1,-1},{-2,-1,-9,-9}};
	float max_res2[4]={5,8,3,-1};
	max_row(m2,max);
	assert(iguales(max,max_res2));
	return 0;
}	


