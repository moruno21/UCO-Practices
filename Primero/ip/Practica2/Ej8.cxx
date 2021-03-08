#include <iostream>
using namespace std;
int main(){
	int num,b,c,n;
	cout<<"¿De cuantos numeros quiere que sea la sucesion"<<endl;//Sucesion de Fibonacci
	cin>>num;
	b=0,c=1;
	while (num>=0){
		n=b+c;
		b=c;
		c=n;
		cout<<n<<endl;
		num--;
	}
cin.ignore();
cin.get();
}
		