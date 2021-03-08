//Archivo crupier_unittest.cc
//Tests para la clase Crupier

#include "crupier.h"
#include "gtest/gtest.h"

TEST(Crupier, ConstructorParametrosDefecto) {
  Crupier c("12345678", "1");
  
  EXPECT_EQ("12345678", c.getDNI());
  EXPECT_EQ("1", c.getCodigo());
  EXPECT_EQ("", c.getNombre());
  EXPECT_EQ("", c.getApellidos());
  EXPECT_EQ("", c.getDireccion());
  EXPECT_EQ("", c.getLocalidad());
  EXPECT_EQ("", c.getProvincia());
  EXPECT_EQ("", c.getPais());
  EXPECT_EQ(", ", c.getApellidosyNombre());
}

TEST(Crupier, ConstructorParametros) {
  Crupier c("12345678", "2", "Antonio", "Moruno", 19, "C/ Adelfa 1", "Cordoba", "Cordoba", "España");

  
  EXPECT_EQ("12345678", c.getDNI());
  EXPECT_EQ("2", c.getCodigo());
  EXPECT_EQ("Antonio", c.getNombre());
  EXPECT_EQ("Moruno", c.getApellidos());
  EXPECT_EQ("C/ Adelfa 1", c.getDireccion());
  EXPECT_EQ("Cordoba", c.getLocalidad());
  EXPECT_EQ("Cordoba", c.getProvincia());
  EXPECT_EQ("España", c.getPais());
  EXPECT_EQ("Moruno, Antonio", c.getApellidosyNombre());
}

TEST(Crupier, ConstructorCopiaDefecto) {
  Crupier c("87654321", "3", "Carlos", "Moruno",30, "C/ Adelfa 1", "Montilla", "Cordoba", "España");
  Crupier d(c);
  
  EXPECT_EQ("87654321", d.getDNI());
  EXPECT_EQ("3", d.getCodigo());
  EXPECT_EQ("Carlos", d.getNombre());
  EXPECT_EQ("Moruno", d.getApellidos());
  EXPECT_EQ("C/ Adelfa 1", d.getDireccion());
  EXPECT_EQ("Montilla", d.getLocalidad());
  EXPECT_EQ("Cordoba", d.getProvincia());
  EXPECT_EQ("España", d.getPais());
  EXPECT_EQ("Moruno, Carlos", d.getApellidosyNombre());
}

TEST(Crupier, OperadorIgual) {
  Crupier c("87654321", "3", "Carlos", "Moruno",30, "C/ Adelfa 1", "Montilla", "Cordoba", "España");
  Crupier d("11111111", "4");
  d=c;

  EXPECT_EQ("87654321", d.getDNI());
  EXPECT_EQ("3", d.getCodigo());
  EXPECT_EQ("Carlos", d.getNombre());
  EXPECT_EQ("Moruno", d.getApellidos());
  EXPECT_EQ("C/ Adelfa 1", d.getDireccion());
  EXPECT_EQ("Montilla", d.getLocalidad());
  EXPECT_EQ("Cordoba", d.getProvincia());
  EXPECT_EQ("España", d.getPais());
  EXPECT_EQ("Moruno, Carlos", d.getApellidosyNombre());
}
