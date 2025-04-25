//#define BRIGHTNESS 255

#include <A15RGB.h>
A15RGB diode(9, 10, 11);
//A15RGB diode(9, 10, 11, GENERAL_ANODE);

void setup() {
  //diode.setBrightness(255);
}

void loop() {
  diode.gradient(255, 0, 0, 0, 0, 255);
  //diode.gradient(0xFF, 0, 0, 0, 0, 0xFF);
  //diode.gradient(RED);
}
