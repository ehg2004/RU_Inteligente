#pragma once

#include <Arduino.h>

#define MAX 7

// #include <ros.h>
// #include <std_msgs/Int16MultiArray.h>

using namespace std;

class Carrinho
{
private:
  // ros::NodeHandle  *nh;
  // std_msgs::Int16MultiArray *int_msg;
  // ros::Publisher *pub_int;
  class Item
  {
  private:
    int code;
    String name;
    int price;
  public:
    Item(int n = 0);
    String getName();
    int getValor();
    int getCode();
    ~Item();
  };
  int nItems;
  Item items[MAX];
public:
  //Carrinho();
  Carrinho(    
    // ros::NodeHandle  *_nh ,
    // std_msgs::Int16MultiArray *_int_msg ,
    // ros::Publisher *_pub_int
     );
  ~Carrinho();
  String getItemName(int i);
  int getNItems();
  bool setItem(int n);
  void reset();
  bool deleteItem(int n);
  int getValor();
  int16_t* pub_items();
};
