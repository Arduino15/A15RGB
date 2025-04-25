//#define BRIGHTNESS 255

#include <A15RGB.h>
A15RGB diode(9, 10, 11); // 9 - RED, 10 - GREEN, 11 - BLUE

void setup() {
  //diode.setBrightness(255);
  diode.RGB(255, 0, 0);
  //diode.RGB(RED);

}

void loop() {
}
