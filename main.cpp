#include <iostream>
#include "Sculptor.h"
using namespace std;

int main(void){
  Sculptor ufo(57,57,57);

  ufo.setColor(0.3, 0.3, 0.5, 1.0); // seta a cor pra cinza
  ufo.putEllipsoid(25, 25, 25, 4, 25, 25); // faz a elipse (painel de controle)

  ufo.setColor(0.5, 0.5, 0.5, 1.0); // seta a cor pra azul claro
  ufo.putSphere(31, 25, 25, 16); // faz a esfera 

  ufo.setColor(1.0, 1.0, 1.0, 1.0); // seta a cor para branco
  ufo.putBox(47, 51, 24, 26, 24, 26); // faz a antena
  ufo.putBox(51, 52, 23, 27, 23, 27); // detalhe da antena

  ufo.setColor(0, 0, 0, 1.0); // seta a cor para preto
  ufo.putBox(14, 23, 23, 25, 43, 45); // faz a primeira perna
  ufo.putBox(13, 14, 22, 26, 42, 46); // detalhe da primeira perna

  ufo.setColor(0, 0, 0, 0); // seta a cor para preto
  ufo.putBox(14, 23, 23, 25, 6, 8); // faz a segunda perna
  ufo.putBox(13, 14, 22, 26, 5, 9); // detalhe da segunda perna

  ufo.setColor(0, 0, 0, 1.0); // seta a cor para preto
  ufo.putBox(14, 23, 43, 45, 23, 25); // faz a terceira perna
  ufo.putBox(13, 14, 42, 46, 22, 26); // detalhe da terceira perna
  
  ufo.setColor(0, 0, 0, 1.0); // seta a cor para preto
  ufo.putBox(14, 23, 6, 8, 23, 25); // faz a quarta perna
  ufo.putBox(13, 14, 5, 9, 22, 26); // detalhe da quarta perna
  
  ufo.writeOFF((char*)"ufo.off");
  return 0;
}
