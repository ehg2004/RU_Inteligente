#include "Carrinho.h"

Carrinho::Carrinho()
{
  nItems = 0;
}

Carrinho::~Carrinho()
{
}

String Carrinho::getItemName(int i)
{
  return items[i].getName();
}

int Carrinho::getNItems()
{
  return nItems;
}

bool Carrinho::setItem(int n)
{
  if(nItems < MAX )
  {
    items[nItems] = Item(n);
    nItems++;
    return true;
  }
  return false;
}

void Carrinho::reset()
{
  nItems = 0;
}

Carrinho::Item::Item(int n)
{
  code = n;
  switch (n)
  {
  case 1:
    name = String("Almoco");
    price = 3;
    break;
  
  case 2:
    name = String("Jantar");
    price = 3;
    break;
  
  case 3:
    name = String("Pao de Queijo");
    price = 2;
    break;
  
  case 4:
    name = String(n);
    price = 1;
    break;
  
  case 5:
    name = String(n);
    price = 1;
    break;
  
  case 6:
    name = String(n);
    price = 1;
    break;
  
  case 7:
    name = String(n);
    price = 1;
    break;

  case 8:
    name = String(n);
    price = 1;
    break;
  
  case 9:
    name = String(n);
    price = 1;
    break;
  
  default:
    break;
  }
}

Carrinho::Item::~Item()
{
  
}

String Carrinho::Item::getName()
{
  return name;
}

int Carrinho::Item::getValor()
{
  return price;
}

bool Carrinho::deleteItem(int n)
{
  if(n > nItems-1)
  {
    return false;
  }
  if(n != nItems)
  {
    items[n]=items[nItems-1];
  } 
  nItems--;
  return true;
}

int Carrinho::getValor()
{
  int valor = 0;
  for (int i = 0; i < nItems; i++)
  {
    valor += items[i].getValor();
  }
  return valor;
}