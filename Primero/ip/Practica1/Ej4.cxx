//Segun el numero el programa dice que dia de la semana es

#include <iostream>
using namespace std;
int main(){
	int x;
	cout<<"Introduzca un número del 1 al 7"<<endl;
	cin>>x;
	if(x==1){
		cout<<"Hoy es lunes y dia laborable"<<endl;
	}
	if(x==2){
		cout<<"Hoy es martes y dia laborable"<<endl;
	}
	if(x==3){
		cout<<"Hoy es miercoles y dia laborable"<<endl;
	}
	if(x==4){
		cout<<"Hoy es jueves y dia laborable"<<endl;
	}
	if(x==5){
		cout<<"Hoy es viernes y dia laborable"<<endl;
	}
	if(x==6){
		cout<<"Hoy es sabado y dia festivo"<<endl;
	}
	if(x==7){
		cout<<"Hoy es domingo y dia festivo"<<endl;
	}
	if(x<1){
		cout<<"Error"<<endl;
	}
	if(x>7){
		cout<<"Error"<<endl;
	}
	cin.ignore();
	cin.get();
}


