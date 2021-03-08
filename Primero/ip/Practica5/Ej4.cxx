#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std; 
float max(float v1[], int n){
	int i=0;
	float b=v1[0];//Asignamos para empezar como mayor de los valores a v1[0]
	for (; i<n; i++){
		if (v1[i]>b){//Entramos solo cuando encontramos un valor mayor que cualquiera de los anteriores
			b=v1[i];//Asignamos el mayor valor a b
		}
	}
	return b;//Devolvemos el mayor de los valores del vector
}
int test();//indica que la funcion test esta mas abajo
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
//funcion de test
int test(){
	int errors=0;


	//test 1(all positive)
	float vec[6]={1,2,30,4,5,6};
	if(  max(vec,6)!=30 ) errors++;

	//test 2(all negative)
	float vec2[6]={-1,-2,-30,-4,-5,-6};
	if(  max(vec2,6)!=-1 ) errors++;

	//test 3 bigger
	float vec3[11]={-1,-2,-30,-4,-5,-6,1,2,5,6,10};
	if(  max(vec3,11)!=10 ) errors++;

	return errors;
}	


