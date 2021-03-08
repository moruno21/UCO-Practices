#include <iostream>
#include <vector>    // necesario para el contenedor vector
#include <cstdlib>   //necesario para rand() y srand()
#include <stdexcept> //necesario para usar la excepcion: out_of_range

using namespace std;

int main(void)
{
vector <int> v(10);
int d,b;

cout << "Ejemplo 4. Uso de  la plantilla de clase 'vector' de la STL de C++\n";

srand(time(NULL)); //establece la semilla a los segundos del sistema

for (int i=0 ; i<v.size() ; i++) v[i] = (1+rand()%10);
for (vector<int>::iterator it = v.begin(); it!=v.end(); ++it)
    cout << *it << " ";
cout << endl;

cout << "Tam = " << v.size() << endl;
cout << endl;

cout << "Insertemos un 77 en la segunda posicion \n" ;
v.insert(v.begin() + 1, 77);
for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

cout << "Tam = " << v.size() << endl;
cout << endl;

cout << "Borramos el elemento en la tercera posicion \n" ;
v.erase(v.begin() + 2);
for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;
cout << "Tam = " << v.size() << endl;
cout << endl;

try {
    v.at(3)=12; // correcto
    cout << "intento acceder al elemento en la pos 34 \n";
    v.at(34)=7;
    }
catch(out_of_range f)
    {
    cout << "Excepcion " << f.what() << endl;
    }

//Cuando este seguro de que no me saldre del 
// rango uso [], pero cuando no lo este (por 
// ejemplo el usuario introduce la posicion), uso at()

cout << "Antes de borrar el vector, ";
cout << "Esta vacio = " << v.empty() << endl;
v.clear();
cout << "Borramos todo el vector, ";
cout << "Esta vacio = " << v.empty() << endl;
cout << "Tam = " << v.size() << endl;
}
