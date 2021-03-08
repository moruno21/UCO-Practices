#include <iostream>
#include <string>
using namespace std;
string concatena (string a, string b){
	string c=a+b;//Concatena la cadena a y b en la cadena c
	return c;
}
int main(){
	string a,b;
	cout<<"Introduzca un texto"<<endl;
	getline(cin,a);
	cout<<"Introduzca un segundo texto"<<endl;
	getline(cin,b);
	cout<<concatena (a,b)<<endl;
cin.ignore();
cin.get();
}