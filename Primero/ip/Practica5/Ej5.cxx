#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std; 
float min (float v1[], int n){
	int i=0;
	float b=v1[0];//Empezamos diciendo que el valor más pequeño es v1[0]
	for (; i<n; i++){
		if (v1[i]<b){
			b=v1[i];//En el momento en el que se encuentre un valor mas pequeño que el anterior, lo guardamos en b hasta acabar
		}
	}
	return b;//Devolvemos el valor más pequeño
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


	//test 1(all positive)
	float vec[6]={1,2,30,4,5,6};
	if(  min(vec,6)!=1 ) errors++;

	//test 2(all negative)
	float vec2[6]={-1,-2,-30,-4,-5,-6};
	if(  min(vec2,6)!=-30 ) errors++;

	//test 3 bigger
	float vec3[11]={-1,-2,-30,-4,-5,-6,1,2,5,6,10};
	if(  min(vec3,11)!=-30 ) errors++;

	return errors;
}	


