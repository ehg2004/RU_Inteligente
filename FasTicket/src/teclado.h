#pragma once

#define CONF 13
#define CANC 14
#define RESET 15

int ler(int n)
{
  if(n < 4)
  {
    return n;
  }
  else if (n < 8)
  {
    return n-1;
  }
  else if (n < 12)
  {
    return n-2;
  }
  return n;
  
  
}