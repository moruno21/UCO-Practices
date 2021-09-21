package Ej2y3;
import java.util.ArrayList;
import java.util.Date;
import Ej1.Espectaculo;
import Ej1.Espectaculo.categoria;
 

public class Programacion {
	private ArrayList<Espectaculo> ListaEspectaculos;
	
	public Programacion() {
		this.ListaEspectaculos = new ArrayList<Espectaculo>();
	}
	
	public void programarEspectaculo(Espectaculo espectaculo) {
		this.ListaEspectaculos.add(espectaculo);
	}
	
	public ArrayList<Espectaculo> verEspectaculos(){
		return this.ListaEspectaculos;
	}
	
	public void imprimirEventos() {
		for(int i = 0; i < this.ListaEspectaculos.size(); i++) {
			System.out.println(this.ListaEspectaculos.get(i).toString());			
		}
	}
	
	public ArrayList<String> verTitulos(){
		ArrayList<String> titulos = new ArrayList<String>();
		for(int i = 0; i < this.ListaEspectaculos.size(); i++) {
			titulos.add(this.ListaEspectaculos.get(i).getTitulo());
		}
		return titulos;
	}
	
	public boolean eliminarEspectaculo(String titulo) {
		for(int i = 0; i < this.ListaEspectaculos.size(); i++) {
			if (this.ListaEspectaculos.get(i).getTitulo() == titulo) {
				this.ListaEspectaculos.remove(i);
				return true;
			}
		}
		return false;
	}
	
	public ArrayList<Espectaculo> verProximosEspectaculos(Date fecha){
		Date hoy = new Date(System.currentTimeMillis());
		if(fecha.before(hoy)) {
			return null;
		}
		ArrayList<Espectaculo> espectaculos = new ArrayList<Espectaculo>();
		for(int i = 0; i < this.ListaEspectaculos.size(); i++) {
			if(this.ListaEspectaculos.get(i).getFecha().before(fecha)) {
				espectaculos.add(this.ListaEspectaculos.get(i));
			}
		}
		return espectaculos;
	}
	
	public ArrayList<Espectaculo> verEspectaculosDisponibles(categoria categoria){
		ArrayList<Espectaculo> espectaculosDisponibles = new ArrayList<Espectaculo>();
		
		for(int i = 0; i < this.ListaEspectaculos.size(); i++) {
			if(this.ListaEspectaculos.get(i).getCategoria() == categoria && this.ListaEspectaculos.get(i).getLocalidadesDisponibles() > 0) {
				espectaculosDisponibles.add(this.ListaEspectaculos.get(i));
			}
		}
		return espectaculosDisponibles;
	}
}
