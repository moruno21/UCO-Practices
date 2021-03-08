#include <iostream>
using namespace std;
int main(){
	int n;
	cout<<"Introduzca el numero de valores con los que desee hacer la media"<<endl;
	cin>>n;
	cout<<"El programa terminará al introducir un numero menor o igual que 0"<<endl;
	int num;
	float suma=0;
	int cont=0;
	int aux=0;	
		while((num>0)&&(n>0)){
			cout<<"Introduzca los valores"<<endl;
				if(n>0){
				cin>>num;
				n=n-1;
				cont++;
				aux++;
				suma=suma+num;
			}			
		}
	cout<<"La media es:"<<suma/cont<<endl;
	cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}