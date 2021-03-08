// listSTL.cc
// Ejemplo de STL list 
// Es un container que optimiza insercion y borrado en cualquier posición.
// Y permite iteración en cualquier dirección. No permite acceso directo.

#include <iostream>
#include <list>
using namespace std;
 struct Apuesta{
    int tipo;
    string valor;
    int cantidad;
 };
 
int main(void)
{
   list<int> L;
   list<float> lf;
   list<Apuesta> apuestas;
   // list<Dados> ld;

   L.push_back(0);              // Insert a new element at the end
   L.push_front(4);             // Insert a new element at the beginning
   L.push_back(5);
   L.push_back(6);
 
   list<int>::iterator it;    // "it" is an iterator for the list L
   list<Apuesta>::iterator itla;
   
   it=L.begin(); // L.begin() is the pointer to the first list element
   L.insert(++L.begin(),2);     // Insert "2" before position of first argument
   advance(it,3); // O bien ++, next(), prev()
   L.insert(it,77);

   for(it=L.begin(); it != L.end(); ++it) cout << *it << " "; 
               // if "it" is equal to L.end(), "it" is after the last list element
   cout << endl;  
   cout << "L.size()= " << L.size() << endl;
   return 0;
}
