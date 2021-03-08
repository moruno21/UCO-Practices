#include <iostream>
#include <vector>
#include <cstdlib>    //necesario para rand() y srand()
#include <exception>  //Necesario para derivar de la clase exception

using namespace std;

class ExcepcionNoEncontrado : public exception {
public:
	ExcepcionNoEncontrado():exception(){};
	const char* what();
};

const char* ExcepcionNoEncontrado::what() 
{
	return ("Excepcion: Elemento No Encontrado en el Vector");
}


int busqueda(vector<int> v, int x)
{
	int i;
	bool encontrado=false;

	for (i=0; i<v.size();i++) 
    		if (v[i]==x) 
       		{
       		encontrado=true;
       		break;
       		}
	if (encontrado) return i;
	else throw ExcepcionNoEncontrado(); //Lanza un objeto
	return (0);
}


int main(void)
{
	vector <int> v(10);
	int i,j;

	cout << "Ejemplo 3 de Excepciones en C++ \n";

	srand(time(NULL)); //establece la semilla a los segundos del sistema
	for (int i=0;i<v.size();i++)v[i]=(1+rand()%10);
	for (int i=0;i<v.size();i++) cout << v[i] << " ";
	cout << endl;
	cout << "introduce el elemento a buscar ";
	cin >> i;

	try {
	    cout << "Estoy dentro del bloque try \n";
	    j=busqueda(v,i);
	    cout << "El elemento " << v[j] << " esta en la pos "<< j << endl;
	    cout << "Estoy despues del throw \n";
	}
	catch (ExcepcionNoEncontrado &ex) { //coge la referencia del objeto, no es necesario
						// ...coger la copia y se ahorra memoria.
	    cout << "Error capturado " << ex.what() << endl;
	}
	catch(...) {
	    cout << "Error capturado por defecto \n";
    	}

	cout << "Fin \n";
	return (0);
}
