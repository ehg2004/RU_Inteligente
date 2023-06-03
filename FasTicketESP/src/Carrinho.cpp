#include "Carrinho.h"

Carrinho::Carrinho(
    // ros::NodeHandle * _nh,
    // std_msgs::Int16MultiArray *_int_msg,
    // ros::Publisher *_pub_int
)//:nh(_nh),int_msg(_int_msg),pub_int(_pub_int)
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
    name = String(F("Almoco"));
    price = 3;
    break;
  
  case 2:
    name = String(F("Jantar"));
    price = 3;
    break;
  
  case 3:
    name = String(F("Pao de Queijo"));
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

int Carrinho::Item::getCode()
{
  return code;
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

int16_t* Carrinho::pub_items()
{
  int16_t * data =(int16_t *)malloc(nItems*sizeof(int16_t));
  for (int i = 0; i < nItems; i++)
  {
    data[i]=items[i].getCode();
  }
  // int_msg->data=data;
  // pub_int->publish(int_msg);
  // int_msg->data = NULL;
  return data;
}