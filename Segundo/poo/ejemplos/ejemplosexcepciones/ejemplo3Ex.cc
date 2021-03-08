#include <iostream>
#include <typeinfo>

using namespace std;

class Rango{};

int main(void)
{
int i(1);
float f(1.2);
double d(2.3);


cout << "Ejemplo 1 de Excepciones en C++ \n";

cout << "con una excepcion de tipo: " << typeid(f).name() << endl;

try {
    cout << "Estoy dentro del bloque try \n";
    //throw f;
    throw Rango();
    cout << "Estoy despues del throw \n";
    }
catch (int i)
    {
    cout << "Error capturado, su valor entero es " << i << endl;
    }
catch (float i)
    {
    cout << "Error capturado, su valor float es " << i << endl;
    }
catch (double i)
    {
    cout << "Error capturado, su valor double es " << i << endl;
    }
catch (Rango)
{
  cout << "Error capturado, Rango"<< endl;
}
/*catch(...)
    {
    cout << "Error capturado por defecto \n";
    }*/
//Si no se captura la excepcion el programa aborta la ejecucion inmediatamente
cout << "Fin \n";
return (0);
}
