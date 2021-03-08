#include <iostream>

using namespace std;

enum excepcion{NEGATIVO, CERO};

int funcion(int a)
{
	if (a==0) throw CERO;
	else if (a<0) throw NEGATIVO;
	     else return 1;
}

int main(void)
{
	int i;
	cout << "Ejemplo 2 de Excepciones en C++ \n";
	cout << "Introduce un entero ";
	cin >> i;
	try {
	funcion(i);
	}
	catch (excepcion e) {
	switch(e) {
		case NEGATIVO:
			cout << "Excepcion: valor negativo \n";
			break;
		case CERO:
			cout << "Excepcion: valor igual a cero \n";
			break;
	}
	}
	return (0);
}
