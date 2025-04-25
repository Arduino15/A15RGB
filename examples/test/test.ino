//#define BRIGHTNESS 255

#include <A15RGB.h>
A15RGB diode(9, 10, 11);
//A15RGB diode(9, 10, 11, GENERAL_ANODE);

uint32_t timer;

void setup() {
  //diode.setBrightness(255);
  diode.RGB(255, 255, 0);
  delay(1000);
  diode.RGB(OCEAN);
  delay(1000);
  diode.HSV(355, 100, 100);
  delay(1000);
  diode.palette(SPRING_GREEN, WHITE);
  delay(1000);
  diode.off();
  delay(500);
  timer = millis();
}

void loop() {
  if (timer >= 2000 && timer < 4000)
    diode.gradient(0, 255, 255, 255, 0, 0, 4);
  else if (timer >= 4000 && timer < 6000)
    diode.gradient(GREEN, ORANGE, 4);
  else if (timer >= 6000 && timer < 8000)
    diode.blinking(255, 0, 255, 500);
  else if (timer >= 8000 && timer < 10000)
    diode.blinking(TURQUOISE, 250);
  else if (timer >= 10000 && timer < 15000)
    diode.smoothBlinking(255, 255, 180, 600, 70);
  else if (timer >= 15000 && timer < 20000)
    diode.smoothBlinking(RASPBERRY, 1000, 50);
  else
    diode.smoothBlinking(random(20, 255), random(20, 255), random(20, 255), 1000, 70);
    
  timer = millis();
}
