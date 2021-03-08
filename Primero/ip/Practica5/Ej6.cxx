#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std; 
bool soniguales(float v1[], float v2[], int n){
	bool res;
	for (int i=0; i<n; i++){
		if (v1[i]==v2[i]){
			res=true;//Guardaremos constantemente true en la variable res, siempre que los valores evaluados sean iguales
		}
		else {
			res=false;
			return res;	//Con que un solo elemento sea diferente, devolvemos false y acabamos el programa
		}
	}
	return res;

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
	float vec2[6]={1,2,30,4,5,6};
	float vec3[6]={1,2,30,4,5,7};
	float vec4[6]={1,2,-1,4,5,6};
	float vec5[6]={1,1,1,1,1,1};

	if(  soniguales(vec,vec2,6)==false ) errors++;
	if(  soniguales(vec,vec3,6)==true ) errors++;
	if(  soniguales(vec,vec4,6)==true ) errors++;
	if(  soniguales(vec5,vec5,6)==false ) errors++;

	return errors;
}	


