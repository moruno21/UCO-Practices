//Archivo jugador_unittest.cc
//Tests para la clase Jugador

#include <fstream>
#include <list>
#include "jugador.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Jugador, ConstructorParametrosDefecto) {
  Jugador j("12345678", "1");
  
  EXPECT_EQ("12345678", j.getDNI());
  EXPECT_EQ("1", j.getCodigo());
  EXPECT_EQ("", j.getNombre());
  EXPECT_EQ("", j.getApellidos());
  EXPECT_EQ("", j.getDireccion());
  EXPECT_EQ("", j.getLocalidad());
  EXPECT_EQ("", j.getProvincia());
  EXPECT_EQ("", j.getPais());
  EXPECT_EQ(", ", j.getApellidosyNombre());
  EXPECT_EQ(1000, j.getDinero());
  
}

TEST(Jugador, ConstructorParametros) {
  Jugador j("12345678", "2", "Antonio", "Moruno", 19, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");

  EXPECT_EQ("12345678", j.getDNI());
  EXPECT_EQ("2", j.getCodigo());
  EXPECT_EQ("Antonio", j.getNombre());
  EXPECT_EQ("Moruno", j.getApellidos());
  EXPECT_EQ("C/ Adelfa 1", j.getDireccion());
  EXPECT_EQ("Cordoba", j.getLocalidad());
  EXPECT_EQ("Cordoba", j.getProvincia());
  EXPECT_EQ("España", j.getPais());
  EXPECT_EQ("Moruno, Antonio", j.getApellidosyNombre());
  EXPECT_EQ(1000, j.getDinero());

}

TEST(Jugador, Modificadores) {              //Hacemos tests a algunas funciones modificadoras set
  Jugador j("12345678", "1");
  std::string nombre = "Pepe";
  j.setNombre(nombre);
  EXPECT_EQ("Pepe", j.getNombre());

  std::string apellido = "Moral";
  j.setApellidos(apellido);
  EXPECT_EQ("Moral", j.getApellidos());

  std::string pais = "Francia";
  j.setPais(pais);
  EXPECT_EQ("Francia", j.getPais());

  std::string localidad = "Toulouse";
  j.setLocalidad(localidad);
  EXPECT_EQ("Toulouse", j.getLocalidad());
}

TEST(Jugador, setDineroygetDinero) {
  Jugador j("12345678", "1");

  EXPECT_EQ(1000, j.getDinero());
  j.setDinero(50);
  EXPECT_EQ(50, j.getDinero());
}

TEST(Jugador, setCodigoygetCodigo) {
  Jugador j("12345678", "1");

  EXPECT_EQ("1", j.getCodigo());
  j.setCodigo("2");
  EXPECT_EQ("2", j.getCodigo());
}

TEST(Jugador, setApuestasygetApuestasVacio) {
  Jugador j("33XX", "1");
  list<Apuesta> l;
  l= j.getApuestas();
  EXPECT_TRUE(l.empty());
}

TEST(Jugador, setApuestasygetApuestas) {
  Jugador j("33XX", "1");
  string fichero=j.getDNI()+".txt";
  ofstream salida(fichero.c_str());
  salida << 1 << "," << "10" << "," << 15<< "\n";
  salida << 2 << "," << "rojo" << "," << 25<< "\n";
  salida << 3 << "," << "par" << "," << 35<< "\n";
  salida << 4 << "," << "bajo" << "," << 45<< "\n";
  salida.close();
  list<Apuesta> l;
  j.setApuestas();
  l= j.getApuestas();
  EXPECT_EQ(4, l.size());
  list<Apuesta>::iterator i;
  i=l.begin();
  EXPECT_EQ(1, (*i).tipo);
  EXPECT_EQ("10", (*i).valor);
  EXPECT_EQ(15, (*i).cantidad);
  i++;
  EXPECT_EQ(2, (*i).tipo);
  EXPECT_EQ("rojo", (*i).valor);
  EXPECT_EQ(25, (*i).cantidad);
  i++;
  EXPECT_EQ(3, (*i).tipo);
  EXPECT_EQ("par", (*i).valor);
  EXPECT_EQ(35, (*i).cantidad);
  i++;
  EXPECT_EQ(4, (*i).tipo);
  EXPECT_EQ("bajo", (*i).valor);
  EXPECT_EQ(45, (*i).cantidad);
}

