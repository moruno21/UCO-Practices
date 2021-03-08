#include <iostream>
using namespace std;
int main(){
	int x;
	cout<<"Introduzca un numero entre 1 y 12"<<endl;
	cin>>x;
	if (x==1){
		cout<<"Es enero y tiene 31 dias"<<endl;
	}
	if (x==2){
		cout<<"Es febrero y tiene 28 dias (29 en los años bisiestos)"<<endl;
	}
	if (x==3){
		cout<<"Es marzo y tiene 31 dias"<<endl;
	}
	if (x==4){
		cout<<"Es abril y tiene 30 dias"<<endl;
	}
	if (x==5){
		cout<<"Es mayo y tiene 31 dias"<<endl;
	}
	if (x==6){
		cout<<"Es junio y tiene 30 dias"<<endl;
	}
	if (x==7){
		cout<<"Es julio y tiene 31 dias"<<endl;
	}
	if (x==8){
		cout<<"Es agosto y tiene 31 dias"<<endl;
	}
	if (x==9){
		cout<<"Es septiembre y tiene 30 dias"<<endl;
	}
	if (x==10){
		cout<<"Es octubre y tiene 31 dias"<<endl;
	}
	if (x==11){
		cout<<"Es noviembre y tiene 30 dias"<<endl;
	}
	if (x==12){
		cout<<"Es diciembre y tiene 31 dias"<<endl;
	}
	if ((x>7)&&(x<1)){
		cout<<"No existe el mes"<<endl;
	}
cin.ignore();
cin.get();
}