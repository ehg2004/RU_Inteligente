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
  return String();
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
  name = String("AA");
  price = 0;
}

Carrinho::Item::~Item()
{
  
}

bool Carrinho::deleteItem(int n)
{
    return false;
}