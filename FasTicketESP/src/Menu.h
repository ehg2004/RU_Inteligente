#pragma once

#include "Adafruit_ILI9341.h"
#include "Carrinho.h"

#define EstINIC 1
#define EstCARR 2
#define EstCANC 3
#define EstRFID 4
#define EstPGMT 5
#define EstSSAL 6

class Menu
{
private:
  int estado;
  Adafruit_ILI9341* ds;
  Carrinho* car;
  String str;
public:
  Menu();
  void begin(Adafruit_ILI9341* d, Carrinho* c);
  void imprimir();
  void atualizar(int est);
  int getEstado();
  ~Menu();
};
