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
  name = String(n);
  price = 0;
}

Carrinho::Item::~Item()
{
  
}

String Carrinho::Item::getName()
{
  return name;
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