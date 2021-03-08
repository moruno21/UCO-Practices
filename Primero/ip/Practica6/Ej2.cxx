#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 
void sum(float m[4] [4], float m2 [4] [4]){
int i, j;
	for (i=0; i<4; i++){
		for (j=0; j<4; j++){
			m[i] [j]=m[i] [j]+m2[i] [j];//Hace la suma para cada elemento de las matrices
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
int test(){
	
	float m[4][4]={ {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
	float m2[4][4]={ {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};	
	sum(m,m2);	
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			assert( m[i][j]==2*m2[i][j]);
	return 0;
}	


