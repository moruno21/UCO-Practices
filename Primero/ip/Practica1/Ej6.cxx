#include <iostream>
using namespace std;
int main(){
	float media,a,b,c,d;
	cout<<"Introduzca el primer numero"<<endl;
	cin>>a;
	cout<<"Introduzca el segundo numero"<<endl;
	cin>>b;
	cout<<"Introduzca el tercer numero"<<endl;
	cin>>c;
	cout<<"Introduzca el cuarto numero"<<endl;
	cin>>d;
	media=(a+b+c+d)/4;
	cout<<"La media es:"<<media<<endl;
	cin.ignore();
	cin.get();
}