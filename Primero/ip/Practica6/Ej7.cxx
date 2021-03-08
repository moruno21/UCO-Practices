#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 
void min_col(float m[4] [4], float min[4]){
int i,j;
	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			if (i==0){
				min[j]=m[i] [j];//Metemos inicialmente el primer valor de la columna en el vector, para después comprobar si los demás elementos de la columna son mayores o menores que él
			}
			if (min[j]>m[i] [j]){
				min[j]=m[i] [j];//Acaba guardando en el vector min el mínimo elemento de cada columna
			}
		}
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
	float min[4];
	float min_res[4]={1,1,1,1};
	min_col(m,min);
	assert(iguales(min,min_res));
	
	
	float m2[4][4]={ {1,-1,-99999,211},{23,24,12,22},{33,43,-12,3},{124,4613,454,4312}};
	float min_res2[4]={1,-1,-99999,3};
	min_col(m2,min);
 	assert(iguales(min,min_res2));
	return 0;
	
	
}	


