#include <vector>
#include <list>
#include <iostream>
using namespace std;

int main(){
     vector<int> v = {0, 1, 2, 3, 4, 5};
     list<int> l {55,56,57,58,59,60};
     for (const int n: v) cout << n << "\t";
     cout <<endl; 

     for (int n: l) cout << n << "\t"; // acceso por valor, n es copia de cada elemento.
     cout << endl;

     for (int &n: l) n++; //acceso por referencia y puedo cambiar cada elemento.

     for (const int &n: l) cout << n << "\t"; // referencia cte.
     cout << endl;
     
     for (char c : {'A', 'B', 'C', 'D', 'E'}) // the initializer may be a braced-init-list
        std::cout << c << "\t";
    std::cout << '\n';
}