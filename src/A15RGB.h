#pragma once

#include "colors.h"

#define GENERAL_ANODE 1
#define GENERAL_CATHODE 0

class A15RGB {
  public:
    A15RGB(uint8_t rPin, uint8_t gPin, uint8_t bPin, bool typeDiode = GENERAL_CATHODE):
      _rPin(rPin),
      _gPin(gPin),
      _bPin(bPin),
      _typeDiode(typeDiode) {
      pinMode(_rPin, OUTPUT);
      pinMode(_gPin, OUTPUT);
      pinMode(_bPin, OUTPUT);

#ifdef BRIGHTNESS
      _brightness = BRIGHTNESS;
#endif
    }

    void setBrightness(uint8_t brightness) {
      _brightness = brightness;
    }

    void RGB(uint8_t red, uint8_t green, uint8_t blue) {
      if (_typeDiode == GENERAL_CATHODE) {
        analogWrite(_rPin, (red * _brightness) / 255);
        analogWrite(_gPin, (green * _brightness) / 255);
        analogWrite(_bPin, (blue * _brightness) / 255);
      }
      else {
        analogWrite(_rPin, 255 - (red * _brightness) / 255);
        analogWrite(_gPin, 255 - (green * _brightness) / 255);
        analogWrite(_bPin, 255 - (blue * _brightness) / 255);
      }
    }

    void RGB(colors* color) {
      RGB(color);
    }

    void HSV(uint16_t H, uint8_t S, uint8_t V) {
      float s = S / 100;
      float v = V / 100;
      float C = s * v;
      float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
      float m = v - C;
      float r, g, b;
      if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
      }
      else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
      }
      else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
      }
      else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
      }
      else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
      }
      else {
        r = C, g = 0, b = X;
      }
      uint8_t R = (r + m) * 255;
      uint8_t G = (g + m) * 255;
      uint8_t B = (b + m) * 255;

      RGB(R, G, B);
    }

    void palette(uint8_t r0, uint8_t g0, uint8_t b0, uint8_t r1, uint8_t g1, uint8_t b1) {
      RGB(uint8_t((r0 + r1) / 2), uint8_t((g0 + g1) / 2), uint8_t((b0 + b1) / 2));
    }

    void palette(colors* color, colors* color0) {
      palette(color, color0);
    }

    void off() {
      RGB(0, 0, 0);
    }

    void blinking(uint8_t r, uint8_t g, uint8_t b, uint16_t speedBlinking = 500) {
      static bool stateDiode = 0;
      static uint32_t timer = millis();
      if (millis() - timer >= speedBlinking) {
        timer = millis();
        stateDiode = !stateDiode;
        if (stateDiode) off();
        else RGB(r, g, b);
      }
    }

    void blinking(colors* color, uint16_t speedBlinking = 500) {
      blinking(color, speedBlinking);
    }

    void smoothBlinking(uint8_t r, uint8_t g, uint8_t b, uint16_t period = 1000, uint8_t minBrightness = 30, uint8_t framerate = 200) {
      static bool increasing = true;
      static uint32_t lastUpdate = 0;
      static float brightness = minBrightness;
      if (minBrightness > 255) minBrightness = 255;
      uint32_t interval = period / (2 * framerate);
      if (millis() - lastUpdate >= interval) {
        lastUpdate = millis();
        float brightnessRange = 255.0 - minBrightness;
        float step = brightnessRange / (period / (2.0 * interval));

        if (increasing) {
          brightness += step;
          if (brightness >= 255.0) {
            brightness = 255.0;
            increasing = false;
          }
        } else {
          brightness -= step;
          if (brightness <= minBrightness) {
            brightness = minBrightness;
            increasing = true;
          }
        }
        RGB((r * (uint8_t)brightness) / 255, (g * (uint8_t)brightness) / 255, (b * (uint8_t)brightness) / 255);
      }
    }

    void smoothBlinking(colors* color, uint16_t period = 1000, uint8_t framerate = 200) {
      smoothBlinking(color, period, framerate);
    }


    void gradient(uint8_t r, uint8_t g, uint8_t b, uint8_t r0, uint8_t g0, uint8_t b0, uint8_t speedGradient = 100, uint8_t sDGradient = 1) {
      static uint8_t r1 = r;
      static uint8_t g1 = g;
      static uint8_t b1 = b;
      static uint32_t timer = millis();
      if (millis() - timer >= speedGradient && r1 < r0 && g1 < g0 && b1 < b0) {
        timer = millis();
        r1 += sDGradient;
        g1 += sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 < g0 && b1 < b0) {
        timer = millis();
        r1 -= sDGradient;
        g1 += sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && g1 > g0 && b1 < b0) {
        timer = millis();
        r1 += sDGradient;
        g1 -= sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && g1 < g0 && b1 > b0) {
        timer = millis();
        r1 += sDGradient;
        g1 += sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 > g0 && b1 < b0) {
        timer = millis();
        r1 -= sDGradient;
        g1 -= sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 < g0 && b1 > b0) {
        timer = millis();
        r1 -= sDGradient;
        g1 += sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && g1 > g0 && b1 > b0) {
        timer = millis();
        r1 += sDGradient;
        g1 -= sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 > g0 && b1 > b0) {
        timer = millis();
        r1 -= sDGradient;
        g1 -= sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && g1 < g0) {
        timer = millis();
        r1 += sDGradient;
        g1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 < g0) {
        timer = millis();
        r1 -= sDGradient;
        g1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && g1 > g0) {
        timer = millis();
        r1 += sDGradient;
        g1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && g1 > g0) {
        timer = millis();
        r1 -= sDGradient;
        g1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && b1 < b0) {
        timer = millis();
        r1 += sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && b1 < b0) {
        timer = millis();
        r1 -= sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0 && b1 > b0) {
        timer = millis();
        r1 += sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0 && b1 > b0) {
        timer = millis();
        r1 -= sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 < g0 && b1 < b0) {
        timer = millis();
        g1 += sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 > g0 && b1 < b0) {
        timer = millis();
        g1 -= sDGradient;
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 < g0 && b1 > b0) {
        timer = millis();
        g1 += sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 > g0 && b1 > b0) {
        timer = millis();
        g1 -= sDGradient;
        b1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 < r0) {
        timer = millis();
        r1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 < g0) {
        timer = millis();
        g1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && b1 < b0) {
        timer = millis();
        b1 += sDGradient;
      }
      if (millis() - timer >= speedGradient && r1 > r0) {
        timer = millis();
        r1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && g1 > g0) {
        timer = millis();
        g1 -= sDGradient;
      }
      if (millis() - timer >= speedGradient && b1 > b0) {
        timer = millis();
        b1 -= sDGradient;
      }
      RGB(r1, g1, b1);
    }

    void gradient(colors* color, colors* color0, uint8_t speedGradient = 100, uint8_t sDGradient = 1) {
      gradient(color, color0, speedGradient, sDGradient);
    }

  private:
    const uint8_t _rPin;
    const uint8_t _gPin;
    const uint8_t _bPin;
    const bool _typeDiode;
    uint8_t _brightness = 255;
};
