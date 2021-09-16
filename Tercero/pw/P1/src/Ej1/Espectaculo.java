package Ej1;
import java.util.Date;

public class Espectaculo {

	public enum categoria{
		concierto, obra, monologo
	}
	private String titulo;
	private categoria categoria;
	private String descripcion;
	private Date fecha;
	private int localidadesDisponibles;
	private int localidadesVendidas;
	
	public Espectaculo() {
		
	}
	
	public Espectaculo(String titulo, categoria categoria, String descripcion ) {
		this.titulo = titulo;
		this.categoria = categoria;
		this.descripcion = descripcion;
	}
	
	
	public String getTitulo() {
		return this.titulo;
	}
	
	public categoria getCategoria() {
		return this.categoria;
	}
	
	public String getDescripcion() {
		return this.descripcion;
	}
	
	public Date getFecha(){
		return this.fecha;
	}
	
	public int getLocalidadesDisponibles() {
		return this.localidadesDisponibles;
	}
	
	public int getLocalidadesVendidas() {
		return this.localidadesVendidas;
	}
	
	
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	
	public void setCategoria(categoria categoria) {
		this.categoria = categoria;
	}
	
	public void setDescripcion(String descripcion) {
		this.descripcion = descripcion;
	}
	
	public void setFecha(Date fecha) {
		this.fecha = fecha;
	}
	
	public void setLocalidadesDisponible(int localidadesDisponibles) {
		this.localidadesDisponibles = localidadesDisponibles;
	}
	
	public void setLocalidadesVendidas(int localidadesVendidas) {
		this.localidadesVendidas = localidadesVendidas;
	}
	
	public String toString() {
		String info = "Titulo: " + this.titulo + " // Categoría: " + this.categoria + " // Descripcion: " + this.descripcion + " // Fecha: " + this.fecha + " // Localidades disponibles: " + this.localidadesDisponibles + " // Localidades vendidas: " + this.localidadesVendidas;
		return info;
	}
	
	
}