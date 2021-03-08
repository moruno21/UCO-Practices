#include <iostream>
using namespace std;
int main(){
	int a,b;
	cin>>a;
	for(b=1;a>=1;a=a-1){
		b=b*a;
	}
	cout<<"Su factorial es="<<b<<endl;
cout<<"Fin del programa"<<endl;
cin.ignore();
cin.get();
}
	