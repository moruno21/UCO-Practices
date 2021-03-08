//Archivo persona_unittest.cc
//Tests para la clase Persona

#include "persona.h"
#include "gtest/gtest.h"

TEST(Persona, ConstructorParametrosDefecto) {
  Persona p("12345678");
  
  EXPECT_EQ("12345678", p.getDNI());
  EXPECT_EQ("", p.getNombre());
  EXPECT_EQ("", p.getApellidos());
  EXPECT_EQ("", p.getDireccion());
  EXPECT_EQ("", p.getLocalidad());
  EXPECT_EQ("", p.getProvincia());
  EXPECT_EQ("", p.getPais());
  EXPECT_EQ(0, p.getEdad());
  EXPECT_EQ(", ", p.getApellidosyNombre());
  
}
 


TEST(Persona, ConstructorParametros) {
  Persona p("12345678", "Antonio", "Moruno", 19, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");
  
  EXPECT_EQ("12345678", p.getDNI());
  EXPECT_EQ("Antonio", p.getNombre());
  EXPECT_EQ("Moruno", p.getApellidos());
  EXPECT_EQ(19, p.getEdad());
  EXPECT_EQ("C/ Adelfa 1", p.getDireccion());
  EXPECT_EQ("Cordoba", p.getLocalidad());
  EXPECT_EQ("Cordoba", p.getProvincia());
  EXPECT_EQ("España", p.getPais());
  EXPECT_EQ("Moruno, Antonio", p.getApellidosyNombre());
}


TEST(Persona, Modificadores) {              //Hacemos tests a algunas funciones modificadoras set
  Persona p("12345678");
  std::string nombre = "Pepe";
  p.setNombre(nombre);
  EXPECT_EQ("Pepe", p.getNombre());

  std::string apellido = "Moral";
  p.setApellidos(apellido);
  EXPECT_EQ("Moral", p.getApellidos());

  std::string pais = "Francia";
  p.setPais(pais);
  EXPECT_EQ("Francia", p.getPais());

  std::string localidad = "Toulouse";
  p.setLocalidad(localidad);
  EXPECT_EQ("Toulouse", p.getLocalidad());
}

TEST(Persona, OperadorIgual) {
  Persona p("12345678", "Antonio", "Moruno", 19, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");
  
  Persona q("87654321");
  q=p;                                                      //Primera forma de igualar
  EXPECT_EQ("12345678", q.getDNI());
  EXPECT_EQ("Antonio", q.getNombre());
  EXPECT_EQ("Moruno", q.getApellidos());
  EXPECT_EQ(19, q.getEdad());
  EXPECT_EQ("C/ Adelfa 1", q.getDireccion());
  EXPECT_EQ("Cordoba", q.getLocalidad());
  EXPECT_EQ("Cordoba", q.getProvincia());
  EXPECT_EQ("España", q.getPais());
  EXPECT_EQ("Moruno, Antonio", q.getApellidosyNombre());
  
  Persona r(p);                                             //Segunda forma de igualar
  EXPECT_EQ("12345678", r.getDNI());
  EXPECT_EQ("Antonio", r.getNombre());
  EXPECT_EQ("Moruno", r.getApellidos());
  EXPECT_EQ(19, r.getEdad());
  EXPECT_EQ("C/ Adelfa 1", r.getDireccion());
  EXPECT_EQ("Cordoba", r.getLocalidad());
  EXPECT_EQ("Cordoba", r.getProvincia());
  EXPECT_EQ("España", r.getPais());
  EXPECT_EQ("Moruno, Antonio", r.getApellidosyNombre());
}
 
 TEST(Persona, mayor) {
  Persona p("12345678", "Antonio", "Moruno", 19, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");  //Persona p mayor de edad que luego sera menor de edad

  EXPECT_EQ(true, p.mayor());
  EXPECT_FALSE(p.setEdad(-5));
  EXPECT_TRUE(p.setEdad(7));
  EXPECT_EQ(false, p.mayor());


  Persona q("87654321", "Pepe", "Moruno", 12, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");     //Persona q menor de edad que luego sera mayor de edad

  EXPECT_EQ(false, q.mayor());
  EXPECT_FALSE(q.setEdad(-2));
  EXPECT_TRUE(q.setEdad(20));
  EXPECT_EQ(true, q.mayor());

  
}
