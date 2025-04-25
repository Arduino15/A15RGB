//#define BRIGHTNESS 255

#include <A15RGB.h>
A15RGB diode(9, 10, 11);
//A15RGB diode(9, 10, 11, GENERAL_ANODE);

void setup() {
  //diode.setBrightness(255);
  diode.palette(RED, BLUE); //RED+BLUE=VIOLET
}

void loop() {
}
