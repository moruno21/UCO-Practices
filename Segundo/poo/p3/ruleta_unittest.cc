//Archivo ruleta_unittest.cc
//Tests de la clase Ruleta
//Añadidos al final tests para las funciones esRoja, esPar y esAlta

#include <fstream>
#include <list>
#include "crupier.h"
#include "ruleta.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Ruleta, Constructor) {
  Crupier c("12345678","1");
  Ruleta r(c);
  
  EXPECT_EQ("12345678", r.getCrupier().getDNI());
  EXPECT_EQ("1", r.getCrupier().getCodigo());
  EXPECT_EQ(-1, r.getBola());
  EXPECT_EQ(1000000, r.getBanca());
  EXPECT_TRUE(r.getJugadores().empty());
}

TEST(Ruleta, setBola) {
  Crupier c("12345678","1");
  Ruleta r(c);
  EXPECT_TRUE(r.setBola(25));
  EXPECT_EQ(25, r.getBola());
  EXPECT_FALSE(r.setBola(77));
  EXPECT_EQ(25, r.getBola());
}

TEST(Ruleta, setBanca) {
  Crupier c("12345678","1");
  Ruleta r(c);
  EXPECT_TRUE(r.setBanca(2000000));
  EXPECT_EQ(2000000, r.getBanca());
  EXPECT_FALSE(r.setBanca(-5));
  EXPECT_EQ(2000000, r.getBanca());
}

TEST(Ruleta, getCrupier) {
  Crupier c("12345678","1");
  Crupier d("11111111","2");
  Ruleta r(c);
  d=r.getCrupier();
  EXPECT_EQ("12345678", d.getDNI());
  EXPECT_EQ("1", d.getCodigo());
}

TEST(Ruleta, addJugador) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  EXPECT_TRUE(r.addJugador(j1));
  EXPECT_TRUE(r.addJugador(j2));
  EXPECT_FALSE(r.getJugadores().empty());
  EXPECT_EQ(2, r.getJugadores().size());
  EXPECT_EQ("44XX", r.getJugadores().begin()->getDNI());
  EXPECT_EQ("jugador1", r.getJugadores().begin()->getCodigo());
  EXPECT_EQ("55XX", (--r.getJugadores().end())->getDNI());
  EXPECT_EQ("jugador2", (--r.getJugadores().end())->getCodigo());
  EXPECT_FALSE(r.addJugador(j1));
  EXPECT_FALSE(r.addJugador(j1));
}

TEST(Ruleta, addJugadorFicheros) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);
  string nomfich = r.getJugadores().begin()->getDNI() + ".txt";
  fstream salida(nomfich.c_str(), ios::in);
  EXPECT_TRUE((bool)salida);
  salida.close();
  nomfich = (--r.getJugadores().end())->getDNI() + ".txt";
  salida.open(nomfich.c_str(), ios::in);
  EXPECT_TRUE((bool)salida);
  salida.close();
}

TEST(Ruleta, deleteJugador) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);
  EXPECT_EQ(1,r.deleteJugador(j1));
  EXPECT_EQ(1, r.getJugadores().size());
  EXPECT_EQ("55XX", r.getJugadores().begin()->getDNI());
  EXPECT_EQ("jugador2", r.getJugadores().begin()->getCodigo());
  EXPECT_EQ(1, r.getJugadores().size());
  j1.setDNI("88XX");
  EXPECT_EQ(-2,r.deleteJugador(j1));
  EXPECT_EQ(1,r.deleteJugador(j2));
  EXPECT_EQ(-1,r.deleteJugador(j1));
  EXPECT_EQ(0, r.getJugadores().size());
}

TEST(Ruleta, deleteJugadorDNI) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);
  EXPECT_EQ(1,r.deleteJugador("44XX"));
  EXPECT_EQ(1, r.getJugadores().size());
  EXPECT_EQ("55XX", r.getJugadores().begin()->getDNI());
  EXPECT_EQ("jugador2", r.getJugadores().begin()->getCodigo());
  EXPECT_EQ(1, r.getJugadores().size());
  EXPECT_EQ(-2,r.deleteJugador("88XX"));
  EXPECT_EQ(1,r.deleteJugador("55XX"));
  EXPECT_EQ(-1,r.deleteJugador("55XX"));
  EXPECT_EQ(0, r.getJugadores().size());
}
TEST(Ruleta, deleteJugadorEnMedio) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Jugador j3("66XX","jugador3");
  Jugador j4("77XX","jugador4");
  Jugador j5("88XX","jugador5");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);
  r.addJugador(j3);
  r.addJugador(j4);
  r.addJugador(j5);
  EXPECT_EQ(1,r.deleteJugador("55XX"));
  EXPECT_EQ(4, r.getJugadores().size());
  EXPECT_EQ("44XX", r.getJugadores().begin()->getDNI());
  EXPECT_EQ("jugador1", r.getJugadores().begin()->getCodigo());
  EXPECT_EQ(4, r.getJugadores().size());
  EXPECT_EQ(-2,r.deleteJugador("99XX"));
  EXPECT_EQ(1,r.deleteJugador("77XX"));
  EXPECT_EQ(3, r.getJugadores().size());
}

TEST(Ruleta, escribeLeeJugadores) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);
  r.escribeJugadores();
  Ruleta r2(c);
  r2.leeJugadores();
  EXPECT_FALSE(r2.getJugadores().empty());
  EXPECT_EQ(2, r2.getJugadores().size());
  EXPECT_EQ("44XX", r2.getJugadores().begin()->getDNI());
  EXPECT_EQ("jugador1", r2.getJugadores().begin()->getCodigo());
  EXPECT_EQ("55XX", (--r2.getJugadores().end())->getDNI());
  EXPECT_EQ("jugador2", (--r2.getJugadores().end())->getCodigo());
}

TEST(Ruleta, giraRuleta) {
  Crupier c("12345678","1");
  Ruleta r(c);
  for (int i=0;i<100;i++){
    r.giraRuleta();
    EXPECT_GT(r.getBola(), -1);
    EXPECT_LT(r.getBola(), 37);
  }
}

TEST(Ruleta, getPremios) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);

  ofstream salida("44XX.txt");
  salida << 1 << "," << "10" << "," << 15<< "\n";
  salida << 2 << "," << "rojo" << "," << 25<< "\n";
  salida << 3 << "," << "par" << "," << 35<< "\n";
  salida << 4 << "," << "bajo" << "," << 45<< "\n";
  salida.close();

  salida.open("55XX.txt");
  salida << 2 << "," << "rojo" << "," << 15<< "\n";
  salida << 1 << "," << "15" << "," << 25<< "\n";
  salida << 4 << "," << "alto" << "," << 35<< "\n";
  salida << 3 << "," << "impar" << "," << 45<< "\n";
  salida.close();

  r.setBola(10); // negro, par, bajo
  r.getPremios();
  //44XX -> 1000 + 15*35 - 25 + 35 + 45 = 1580 
  //55XX -> 1000 - 15 - 25 - 35 - 45 = 880
  //banca_ = banca_ - 580 + 120 = 999540
  EXPECT_EQ(1580, r.getJugadores().begin()->getDinero());
  EXPECT_EQ(880, (++r.getJugadores().begin())->getDinero());
  EXPECT_EQ(999540, r.getBanca());
}

TEST(Ruleta, getPremiosCero) {
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
  r.addJugador(j2);

  ofstream salida("44XX.txt");
  salida << 1 << "," << "10" << "," << 10<< "\n";
  salida << 2 << "," << "rojo" << "," << 20<< "\n";
  salida << 3 << "," << "par" << "," << 30<< "\n";
  salida << 4 << "," << "bajo" << "," << 40<< "\n";
  salida.close();

  salida.open("55XX.txt");
  salida << 2 << "," << "rojo" << "," << 50<< "\n";
  salida << 1 << "," << "15" << "," << 60<< "\n";
  salida << 4 << "," << "alto" << "," << 70<< "\n";
  salida << 3 << "," << "impar" << "," << 80<< "\n";
  salida.close();

  r.setBola(0); // jugadores pierden todo
  r.getPremios();
  //44XX -> 1000 - 10 - 20 - 30 - 40 = 900 
  //55XX -> 1000 - 50 - 60 - 70 - 80 = 740
  EXPECT_EQ(900, r.getJugadores().begin()->getDinero());
  EXPECT_EQ(740, (++r.getJugadores().begin())->getDinero());
  EXPECT_EQ(1000360, r.getBanca());
}


TEST(Ruleta, FuncionesRojaAltaPar){
  Crupier c("12345678", "1");
  Ruleta r(c);

  //El 5 es un numero rojo, impar y bajo
  EXPECT_TRUE(r.esRoja(5));
  EXPECT_FALSE(r.esPar(5));
  EXPECT_FALSE(r.esAlta(5));

  //El 28 es un numero negro, par y alto
  EXPECT_FALSE(r.esRoja(28));
  EXPECT_TRUE(r.esPar(28));
  EXPECT_TRUE(r.esAlta(28));

}