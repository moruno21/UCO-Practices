#include <iostream>
#include <string>
using namespace std;
string verificar_dni(string dni){
	string res;
	if (dni.size()!=9){
		res="Error, el dni introducido no tiene 9 caracteres";
		return res;//Finalizara si el dni introducido no tiene 9 caracteres
	}
	for (int i=0; i<8; i++){
		if (!isdigit(dni[i])){
			res="Error. Los 8 primeros caracteres del dni deben ser numericos";
			return res;//Finalizara si uno o varios de los 8 primeros elementos del dni introducido no son digitos
		}
	}
	dni[8]=toupper(dni[8]);//Pasamos la letra del dni introducido a mayuscula
	int numero=stoi(dni);//Pasamos de string (cadena) a int (entero)
	char letras[]= "TRWAGMYFPDXBNJZSQVHLCKE";
	if (dni[8]!=letras[(numero%23)]){//Formulas para comprobar si la letra se corresponde con los 8 digitos del dni introducido
		res="Error, la letra no se corresponde con el numero";
		return res;//Finalizara si la letra del dni introducido no se corresponde con sus 8 digitos
	}
	res="Es correcto";
	return res;//Se finalizara obteniendo que el dni introducido es correcto siempre que no se entre en ninguno de los if anteriores
}
int main(){
	string dni;
	cout<<"Introduzca el dni para comprobar si es correcto o no"<<endl;
	cin>>dni;
	cout<<verificar_dni(dni)<<endl;
cin.ignore();
cin.get();
}