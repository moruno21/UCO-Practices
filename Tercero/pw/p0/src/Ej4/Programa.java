package Ej4;

import Ej1.Espectaculo;
import Ej1.Espectaculo.categoria;
import Ej2y3.Programacion;
import java.util.Date;

public class Programa {
	public static void main(String [] args) {
//		Creamos la programacion que inicialmente esta vacia
		Programacion programacion = new Programacion();
		
//		Creamos los 2 primeros espectaculos con el constructor vacio
		Espectaculo espectaculo1 = new Espectaculo();
		Espectaculo espectaculo2 = new Espectaculo();
		
		
//		Usamos los setters para dar valores a los 2 primeros espectaculos
		espectaculo1.setTitulo("Rey Leon");
		espectaculo1.setCategoria(categoria.obra);
		espectaculo1.setDescripcion("La obra del león");
		espectaculo1.setFecha(new Date(System.currentTimeMillis()*2));
		espectaculo1.setLocalidadesDisponible(0);
		espectaculo1.setLocalidadesVendidas(200);
		
		espectaculo2.setTitulo("Imagine Dragons");
		espectaculo2.setCategoria(categoria.concierto);
		espectaculo2.setDescripcion("El mejor concierto");
		espectaculo2.setFecha(new Date(System.currentTimeMillis()*3));
		espectaculo2.setLocalidadesDisponible(30);
		espectaculo2.setLocalidadesVendidas(100);
		
//		Creamos los siguientes 2 espectaculos mediante el constructor
		Espectaculo espectaculo3 = new Espectaculo("Dani Rovira", categoria.monologo, "Monologo de Dani Rovira");		
		Espectaculo espectaculo4 = new Espectaculo("Coldplay", categoria.concierto, "Concierto de Coldplay");
		
//		Usamos los setters para dar valores al resto de parametros
		espectaculo3.setFecha(new Date(System.currentTimeMillis()*3));
		espectaculo3.setLocalidadesDisponible(10);
		espectaculo3.setLocalidadesVendidas(100);
		
		espectaculo4.setFecha(new Date(System.currentTimeMillis()*4));
		espectaculo4.setLocalidadesDisponible(20);
		espectaculo4.setLocalidadesVendidas(150);
		
//		Añadimos los espectaculos a la programacion
		programacion.programarEspectaculo(espectaculo1);
		programacion.programarEspectaculo(espectaculo2);
		programacion.programarEspectaculo(espectaculo3);
		programacion.programarEspectaculo(espectaculo4);
		
//		Comprobamos las salidas
		System.out.println(programacion.verTitulos());
		System.out.println(programacion.verProximosEspectaculos(new Date(System.currentTimeMillis()*6)));
		System.out.println(programacion.verProximosEspectaculos(new Date(System.currentTimeMillis()/3)));
		System.out.println(programacion.verEspectaculosDisponibles(categoria.concierto));
		
		programacion.eliminarEspectaculo("Coldplay");
		programacion.imprimirEventos();
	}
}
