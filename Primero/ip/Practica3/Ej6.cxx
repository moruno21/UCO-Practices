#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(){
	std::srand(time(0));
	int secreto=rand()%1000;//Con estas lineas de codigo generamos el numero aleatorio
	cout<<"Se ha generado un numero aleatorio entre 0 y 1000. Introduzca un numero para indicarle si este es menor, igual o mayor que el numero secreto. Cuando acierte el numero secreto, el programa finalizara"<<endl;
	int num;
	cin>>num;
	while (num!=secreto){
		if (num>secreto){
		cout<<"El numero introducido es mayor que el secreto. Pruebe de nuevo"<<endl;
		cin>>num;
		}
		if (num<secreto){
		cout<<"El numero introducido es menor que el secreto. Pruebe de nuevo"<<endl;
		cin>>num;
		}
	}
cout<<"Enhorabuena, ha acertado el numero secreto"<<endl;
cin.ignore();
cin.get();
}
	