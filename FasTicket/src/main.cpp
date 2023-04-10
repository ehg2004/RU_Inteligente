#include <Arduino.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TTP229.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(9600);
  tft.begin();

}

void loop() {
  



}