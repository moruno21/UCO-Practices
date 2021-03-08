#include <iostream>
#include <vector>    // necesario para el contenedor vector
#include <cstdlib>   //necesario para rand() y srand()

using namespace std;

int main(void)
{
vector <int> v(10);
vector <float> x(5);
int t;

cout << "Ejemplo 1. Uso de  la plantilla de clase 'vector' de la STL de C++\n";

srand(time(NULL)); //establece la semilla a los segundos del sistema

for (int i=0 ; i<v.size() ; i++) v[i] = (1+rand()%10);
for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

// Algunas metodos de vector: 
cout << "Esta vacio = " << v.empty() << endl;
cout << "Tam = " << v.size() << endl;
cout << "Maximo tam posible = " << v.max_size() << endl;
cout << "Espacio asignado = " << v.capacity() << endl;
cout << "Primer elemento = " << v.front() << " o bien "<< *(v.begin()) << endl;
cout << "Ultimo elemento = " << v.back() << " o bien "<< *(v.end()-1) << endl;


cout << "Introducir datos al vector de floats \n";

for (int i=0 ; i<x.size() ; i++) {
    cout << "Introduce un valor real ";
    cin >> x[i];
    cout << endl;	
}

for (int i=0 ; i<x.size() ; i++) cout << x[i] << " ";
cout << endl;

// Algunas metodos de vector: 
cout << "Esta vacio = " << x.empty() << endl;
cout << "Tam = " << x.size() << endl;
cout << "Maximo tam posible = " << x.max_size() << endl;
cout << "Espacio asignado = " << x.capacity() << endl;
cout << "Primer elemento = " << x.front() << " o bien "<< *(x.begin()) << endl;
cout << "Ultimo elemento = " << x.back() << " o bien "<< *(x.end()-1) << endl;

cout << endl;

cout << "Introduce el tam. del vector " ;
cin >> t;

vector <int> w(t);
for (int i=0 ; i<w.size() ; i++) w[i] = (1+rand()%10);
for (int i=0 ; i<w.size() ; i++) cout << w[i] << " ";
cout << endl;
// Algunas metodos de vector: 
cout << "Esta vacio = " << w.empty() << endl;
cout << "Tam = " << w.size() << endl;
cout << "Maximo tam posible = " << w.max_size() << endl;
cout << "Espacio asignado = " << w.capacity() << endl;
cout << "Primer elemento = " << w.front() << " o bien "<< *(w.begin()) << endl;
cout << "Ultimo elemento = " << w.back() << " o bien "<< *(w.end()-1) << endl;
cout << endl;
}
