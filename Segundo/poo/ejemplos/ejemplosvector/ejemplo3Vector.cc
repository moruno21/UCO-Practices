#include <iostream>
#include <vector>    // necesario para el contenedor vector
#include <cstdlib>   //necesario para rand() y srand()
#include <algorithm> //necesario para sort() y reverse()

using namespace std;

int main(void)
{
vector <int> v(10);
int d,b;

cout << "Ejemplo 3. Uso de  la plantilla de clase 'vector' de la STL de C++\n";

srand(time(NULL)); //establece la semilla a los segundos del sistema

for (int i=0 ; i<v.size() ; i++) v[i] = (1+rand()%10);

// Los iteradores son similares a los punteros 
// begin() apunta al primer elemento 
// y end() apunta al final del vector (despues del ultimo elemento)

cout <<"vector inicial:\n";
for (vector<int>::iterator it = v.begin(); it!=v.end(); ++it)
    cout << *it << " ";
cout << endl;

// Los iteradores se usan con algoritmos
cout <<"vector invertido:\n";

reverse(v.begin(),v.end()); 
// reverse() es un algoritmo de la STL que trabaja con iteradores

for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

cout <<"vector ordenado:\n";
sort(v.begin(),v.end()); // v.begin()+5 ordenar a partir del quinto elemento
// sort() es un algoritmo de la STL que trabaja con iteradores
for (int i=0 ; i<v.size() ; i++) cout << v[i] << " ";
cout << endl;

cout << "Introduce entero a buscar:\n> ";
cin >> b;
if (find(v.begin(),v.end(),b)==v.end()) cout << b <<" no encontrado\n";
else cout << b <<" encontrado\n";
}
