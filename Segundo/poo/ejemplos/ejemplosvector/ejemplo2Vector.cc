#include <iostream>
#include <vector>    // necesario para el contenedor vector
#include <cstdlib>   //necesario para rand() y srand()

using namespace std;

int main(void)
{
vector <int> v(10);
int d;

cout << "Ejemplo 2. Uso de  la plantilla de clase 'vector' de la STL de C++\n";

srand(time(NULL)); //establece la semilla a los segundos del sistema

for (int i=0 ; i<v.size() ; i++) v[i] = (1+rand()%10);
for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

cout << "Añadimos mas elementos al final del vector \n" ;

d = 1+rand()%10;
cout << "Insertamos el elemento " << d;
v.push_back(d);
d = 1+rand()%10;
cout << " y el  " << d << endl;
v.push_back(d);

for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

}
