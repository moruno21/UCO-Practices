package Ej1;


public class Espectaculo {

	enum type{
		concierto, obra, monologo
	}
	private String title;
	private type type;
	private String description;
	private java.util.Date date;
	private int availableTickets;
	private int soldTickets;
	
	public Espectaculo() {
		
	}
	
	public Espectaculo(String title, type type, String description ) {
		this.title = title;
		this.type = type;
		this.description = description;
	}
	
	
	public String getTitle() {
		return this.title;
	}
	
	public type getType() {
		return this.type;
	}
	
	public String getDescription() {
		return this.description;
	}
	
	public java.util.Date getDate(){
		return this.date;
	}
	
	public int getAvailableTickets() {
		return this.availableTickets;
	}
	
	public int getSoldTickets() {
		return this.soldTickets;
	}
	
	
	public void setTitle(String title) {
		this.title = title;
	}
	
	public void setType(type type) {
		this.type = type;
	}
	
	public void setDescription(String description) {
		this.description = description;
	}
	
	public void setDate(java.util.Date date) {
		this.date = date;
	}
	
	public void getAvailableTickets(int availableTickets) {
		this.availableTickets = availableTickets
	}
	
	public void getSoldTickets(int soldTickets) {
		this.soldTickets = soldTickets;
	}
	
	public String toString() {
		String info = "Title: " + this.title + " // Type: " + this.type + " // Description: " + this.description + " // Date: " + this.date + " // Available tickets: " + this.availableTickets + " // Sold tickets: " + this.soldTickets;
		return info;
	}
	
	
}