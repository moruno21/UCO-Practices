//Archivo dados_unittest.cc
//Tests para la clase Dados

#include "dados.h"
#include "gtest/gtest.h"

//Tests constuctor
TEST(Dados, Constructor) {
  Dados d;
  
  EXPECT_EQ(1, d.getDado1());
  EXPECT_EQ(1, d.getDado2());
  EXPECT_EQ(2, d.getSuma());
  EXPECT_EQ(0, d.getDiferencia());
  EXPECT_EQ(0, d.getLanzamientos1());   //Justo despues de declarar un objeto de la clase dados, esta funcion devolvera 0
  EXPECT_EQ(0, d.getLanzamientos2());   //Justo despues de declarar un objeto de la clase dados, esta funcion devolvera 0
  EXPECT_EQ(0, d.getMedia1());          //Justo despues de declarar un objeto de la clase dados, esta funcion devolvera 0
  EXPECT_EQ(0, d.getMedia2());          //Justo despues de declarar un objeto de la clase dados, esta funcion devolvera 0
}

//Tests operación lanzamiento
TEST(Dados, Lanzamiento) {
  Dados d;
  for (int i=0; i<100; i++){
    d.lanzamiento();
    EXPECT_GT(d.getDado1(), 0);
    EXPECT_LT(d.getDado1(), 7);
    EXPECT_GT(d.getDado2(), 0);
    EXPECT_LT(d.getDado2(), 7);
    }

  EXPECT_EQ(100, d.getLanzamientos1());
  EXPECT_EQ(100, d.getLanzamientos2());
}

//Tests operación suma
TEST(Dados, Suma) {
  Dados d;
  EXPECT_EQ(d.getDado1()+d.getDado2(), d.getSuma());
}

//Test operación diferencia
TEST(Dados, Diferencia) {
  Dados d;
  d.setDado1(5);
  d.setDado2(3);
  EXPECT_EQ(d.getDado1() - d.getDado2(), d.getDiferencia());

  d.setDado1(2);
  d.setDado2(6);
  EXPECT_EQ(d.getDado2() - d.getDado1(), d.getDiferencia());
}

//Tests modificadores
TEST(Dados, Modificadores) {
  Dados d;
  int v1[5];
  int v2[5];

  EXPECT_FALSE(d.setDado1(9));
  EXPECT_EQ(1,d.getDado1());
  EXPECT_FALSE(d.setDado1(-9));
  EXPECT_EQ(1,d.getDado1());
  EXPECT_FALSE(d.setDado2(9));
  EXPECT_EQ(1,d.getDado2());
  EXPECT_FALSE(d.setDado2(-9));
  EXPECT_EQ(1,d.getDado2());
  
  EXPECT_TRUE(d.setDado1(3));               //El valor introducido en la funcion setDado1 contara para la media de valores obtenidos para el dado 1
  EXPECT_EQ(3, d.getDado1());
  EXPECT_EQ(3, d.getMedia1());
  d.getUltimos1(v1);
  EXPECT_EQ(3, v1[0]);
  EXPECT_TRUE(d.setDado1(2));               //Volvemos a lanzar el dado para comprobar en la siguiente linea si se hace bien la media
  EXPECT_NEAR(2.5, d.getMedia1(), 0.001);

  EXPECT_TRUE(d.setDado2(2));               //El valor introducido en la funcion setDado2 contara para la media de valores obtenidos para el dado 2
  EXPECT_EQ(2, d.getDado2());
  EXPECT_EQ(2, d.getMedia2());
  d.getUltimos2(v2);
  EXPECT_EQ(2, v2[0]);
  EXPECT_TRUE(d.setDado2(5));               //Volvemos a lanzar el dado para comprobar en la siguiente linea si se hace bien la media
  EXPECT_NEAR(3.5, d.getMedia2(), 0.001);
  
  EXPECT_EQ(7, d.getSuma());
}

//Test getUltimos
TEST(Dados, getUltimos) {
  Dados d;
  int v1[5], v2[5];

  for (int i=1; i<6; i++){
    d.setDado1(i);
  } 
  for (int i=1; i<6; i++){
    d.setDado2(i);
  } 

  d.getUltimos1(v1);
  d.getUltimos2(v2);

  for (int i=0; i<5; i++){
    EXPECT_EQ(5-i, v1[i]);  
  } 
  for (int i=0; i<5; i++){
    EXPECT_EQ(5-i, v2[i]);  
  } 
}
