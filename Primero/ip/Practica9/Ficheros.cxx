#include <string>
#include <iostream>
#include <fstream>
#define ID 5654648
#define SIZE 10
using namespace std;
	struct Alumno{
		string dni;
		int edad;
		float nota;
	};


string verificar_dni(string dni){//Funcion que comprueba si el DNI introducido es correcto o no
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
	res="DNI correcto";
	return res;//Se finalizara obteniendo que el dni introducido es correcto siempre que no se entre en ninguno de los if anteriores
}


Alumno addalumno(){//Funcion para añadir alumnos a la base de datos
	Alumno nuevoalumno;
	cout<<"Introduzca los datos del alumno a continuacion. Nota: Introduzca la letra del DNI en MAYUSCULA"<<endl;
	cout<<"DNI:"<<endl;
	cin>>nuevoalumno.dni;
	cout<<verificar_dni(nuevoalumno.dni)<<endl;//Indicamos al usuario si el DNI que ha introducido es correcto o no, aunque luego podra seguir introduciendo datos independientemente de si el DNI es correcto o no
	cout<<"Edad:"<<endl;
	cin>>nuevoalumno.edad;
	cout<<"Nota:"<<endl;
	cin>>nuevoalumno.nota;
	return nuevoalumno;
}





bool alumnoposicionlibre(Alumno v[], Alumno nuevoalumno, int a){//Funcion que nos permite guardar el alumno que introduzcamos en la primera posicion libre que nos encontramos en el vector
	int pos;
	for (pos=0; pos<a; pos++){
		if (v[pos].dni==""){
			v[pos]=nuevoalumno;
			return true;
		}
	}
	return false;
}




void imprimiralumno( Alumno &nuevoalumno){//Funcion que nos imprimira posteriormente por pantalla los datos de el alumno que desee el usuario
	cout<<"A continuacion se presentan sus datos:"<<endl;
	cout<<"Su dni es: "<<nuevoalumno.dni<<endl;
	cout<<"Su edad es: "<<nuevoalumno.edad<<endl;
	cout<<"Su nota es: "<<nuevoalumno.nota<<endl;
}




int encontraralumno(Alumno alumnos[], int size, string dni){//Funcion que nos permite encontrar al alumno que estemos buscando mediante su DNI
	for (int i=0; i<size; i++){
		if (alumnos[i].dni == dni){
			return i;
		}
	}
	return -1;
}




void imprimirtodos(Alumno alumnos[], int a){//Funcion que nos imprimira posteriormente por pantalla los datos de todos los alumnos
	int cont=0;
	for (int i=0; i<a; i++){
		if (alumnos[i].dni!=""){
			cout<<"Los datos del alumno "<<i+1<<" son:"<<endl;
			imprimiralumno(alumnos[i]);
			cont++;
		}
	}
	cout<<"En total se ha(n) encontrado "<<cont<<" alumno(s)"<<endl;
}

void eliminaralumno( Alumno alumnos[], int elegido){//Funcion que nos permite eliminar el alumno que el usuario desee de la base de datos
	alumnos[elegido].dni="";
}

int lee(string ruta_fichero, Alumno alumnos [SIZE]){
	ifstream file;
	file.open(ruta_fichero);//Intentamos abrir el fichero
	int nuevo=0;
	if (file.is_open()==false){//Si no podemos abrirlo entraremos aqui
		cout<<"Error, el archivo no puede abrirse"<<endl;
		return -1;
	}
	int id= ID;
	int a;
	file>>a;
		if (a!=id){
			return -2;
		}
			while(!file.eof()){//eof hace referencia a end of file
			Alumno aux;
			file>>aux.dni;
			file>>aux.edad;
			file>>aux.nota;
			alumnos [nuevo]=aux;
			nuevo++;
			}//Iremos leyendo todos los datos de los alumnos en el fichero hasta que no quede ninguno
	return nuevo;
}

bool guarda(string ruta_fichero, Alumno alumnos[SIZE], int nalumno){
	ofstream file;
	file.open(ruta_fichero, std::ofstream::trunc);
	if (file.is_open()==false){
		cout<<"Error, el archivo no puede abrirse"<<endl;
		return false;//Acabaremos si el archivo no se puede abrir
	}
	cout<<"Se guardara el archivo"<<endl;
	file<<ID;
	for (int i=0; i<nalumno; i++){
		Alumno aux= alumnos[i];
		file<<aux.dni;
		file<<aux.edad;
		file<<aux.nota;
	}
	return true;//Acabara el programa cuando se pasen los datos de todos los alumnos a fichero
}
		


int main(int argc, char **argv){
	if (argc!=2){
		cout<<"Error, no se ha indicado el nombre del archivo"<<endl;
		return -1;
	}
	string ruta_fichero=argv[1];
	Alumno alumnos [SIZE];
	int nalumnos=lee(ruta_fichero, alumnos);
	if (nalumnos==-2){
		cout<<"Error, archivo no adecuado"<<endl;
		return -1;
	}
	string opcion;
	if (nalumnos==-1){
		do{
			cout<<"¿Desea crear el archivo?"<<endl;
			cout<<"S para Si   N para No"<<endl;
			cin>>opcion;	
			opcion=toupper(opcion[0]);//pasamos la letra introducida por el usuario a mayuscula
		}while((opcion!="S") && (opcion!="N"));
			if (opcion=="N"){
				return -1;
			}
			else{
			cout<<"Se procedera a crear el archivo"<<endl;
			ofstream file;	
			file.open(ruta_fichero);
				if (file.is_open()==false){
				cout<<"Error, espacio insuficiente en la memoria"<<endl;
				return -1;
				}
				else{
				cout<<"Archivo creado y guardado con exito"<<endl;
				nalumnos=0;
				}
			}
	}

	int opcionmenu=0;//Opcion del menu
	cout<<"Bienvenido a la base de datos de alumnos. Por favor, seleccione la accion a realizar"<<endl;
	do{
	cout<<"1. Añadir alumno"<<endl; 
	cout<<"2. Imprimir datos alumno"<<endl; 
	cout<<"3. Imprimir datos de todos los alumnos"<<endl; 
	cout<<"4. Modificar alumno"<<endl; 
	cout<<"5. Eliminar alumno"<<endl; 
	cout<<"6. Salir"<<endl;
	cin>>opcionmenu;
	switch(opcionmenu){//Evaluamos que opcion del menu ha introducido el usuario
		


		case 1:{
		Alumno nuevoalumno= addalumno();
		if (!alumnoposicionlibre(alumnos, nuevoalumno, 10)){//Solo entraremos si el vector esta lleno y no pudieramos introducir mas alumnos en la base de datos
			cout<<"Error, la base de datos esta llena"<<endl;
		}
		else{//Entraremos si el alumno se ha guardado en la base de datos correctamente
			cout<<"Alumno guardado con exito"<<endl;
		}
		}break;
		



		case 2:{
		cout<<"Introduzca el DNI del alumno que este buscando"<<endl;
		string dnibuscado;
		cin>>dnibuscado;
		int i= encontraralumno(alumnos, 10, dnibuscado);//Creamos una variable que tenga el valor del resultado de la funcion encontraralumno
			if (i!=-1){
				cout<<"Alumno encontrado con exito"<<endl;
				imprimiralumno(alumnos[i]);
			}
			else{
				cout<<"Error, el alumno no existe en la base de datos o bien el DNI introducido no existe"<<endl;
			}
		}break;
		

		case 3:{
		imprimirtodos(alumnos, 10);
		}break;
		

		case 4:{
			cout<<"Introduzca el DNI del alumno que quiera modificar"<<endl;
			string dnimodificado;
			cin>>dnimodificado;
			int i= encontraralumno(alumnos, 10, dnimodificado);//Volvemos a crear una variable que valdra lo que valga en este caso la funcion encontraralumno
				if (i!=-1){//Solo entramos si encontramos un alumno cuyo DNI sea el introducido por el usuario
				cout<<"Alumno encontrado con exito. Introduzca a continuacion los datos del nuevo alumno"<<endl;
				Alumno nuevoalumno=addalumno();//Pedimos de nuevo al usuario que introduzca los datos del nuevo alumno llamando a la funcion addalumno
				alumnos [i]=nuevoalumno;
				cout<<"Alumno modificado exitosamente"<<endl;
				}
				else{//Entramos si no encontramos un alumno en la base de datos con el DNI introducido por el usuario
					cout<<"Error, el alumno no existe en la base de datos o bien el DNI introducido no existe"<<endl;
				}
				
		}break;
		

		case 5:{
			cout<<"Introduzca el DNI del alumno que quiera eliminar"<<endl;
			string dnieliminado;
			cin>>dnieliminado;
			int i= encontraralumno(alumnos, 10, dnieliminado);
			if (i!=-1){//Entramos si encontramos al alumno
				cout<<"Alumno encontrado y eliminado con exito"<<endl;
				eliminaralumno(alumnos, i);//Eliminamos al alumno dejando su posicion en el vector vacia
				}
				else{
					cout<<"Error, el alumno no existe en la base de datos o bien el DNI introducido no existe"<<endl;
				}
			
		}break;
		case 6:{//En el caso de que el usuario pulse 6, saldra lo siguiente por pantalla y finalizaremos el programa
			cout<<"Se cerrara el programa a continuacion"<<endl;
		}break; 
		default:{//Entraremos aqui siempre y cuando el usuario introduzca un numero distinto de 1, 2, 3, 4, 5 o 6
			cout<<"Error, seleccione una opcion valida"<<endl;
		}
	}
	}while (opcionmenu!=6);//El usuario podra interactuar con el menu todas la veces que quiera hasta que pulse la tecla 6, correspondiente a finalizar el programa
cin.ignore();
cin.get();
}