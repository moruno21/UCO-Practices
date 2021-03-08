#include <iostream>
using namespace std;
int main(){
	int dia;
	cout<<"Introduzca un numero del 1 al 7"<<endl;
	cin>> dia;
	switch(dia){
	case 1:{
		cout<<"Hoy es lunes"<<endl;
	}break;
	case 2:{
		cout<<"Hoy es martes"<<endl;
	}break;
	case 3:{
		cout<<"Hoy es miercoles"<<endl;
	}break;	
	case 4:{
		cout<<"Hoy es jueves"<<endl;
	}break;
	case 5:{
		cout<<"Hoy es viernes"<<endl;
	}break;
	case 6:{
		cout<<"Hoy es sabado"<<endl;
	}break;
	case 7:{
		cout<<"Hoy es domingo"<<endl;
	}break;
	default:{
		cout<<"Error"<<endl;
		}
	}
cin.ignore();
cin.get();
}