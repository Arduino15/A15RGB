[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/Arduino15Libs)

# A15RGB 
Библиотека для очень лёгкого управления RGB светодиодом!

[скачать ZIP-библиотеку](https://codeload.github.com/Arduino15/A15RGB/zip/refs/heads/main)

## Подключение/инициализация
```cpp
#include <A15RGB.h>                                                      // подключение
A15RGB diode(uint8_t rPin, uint8_t gPin, uint8_t bPin, bool typeDiode);  // пин R, пин G, пин B, тип диода (GENERAL_CATHODE/GENERAL_ANODE), по умолчанию стоит GENERAL_CATHODE
```
## функции
```cpp
void setBrightness(uint8_t brightness);                //настройка яркости, 0-255
void RGB(uint8_t red, uint8_t green, uint8_t blue);    //цвет RGB
void RGB(colors* color);                               //цвет из структуры
void HSV(uint16_t H, uint8_t S, uint8_t V);            //цвет HSV, Hue: 0-360; Saturation: 0-100; Value: 0-100
void palette(uint8_t r0, uint8_t g0, uint8_t b0, uint8_t r1, uint8_t g1, uint8_t b1);  //палетка (смешение оттенков, цветовая модель RGB)
void palette(colors* color, colors* color0);                                           //палетка по цветам из структуры
void off();            //выключение светодиода
void blinking(uint8_t r, uint8_t g, uint8_t b, uint16_t speedBlinking = 500);    //мигание (R, G, B, скорость)
void blinking(colors* color, uint16_t speedBlinking = 500);                      //мигание (цвет из структуры, скорость)
void smoothBlinking(uint8_t r, uint8_t g, uint8_t b, uint16_t period = 1000, uint8_t minBrightness = 30, uint8_t framerate = 200);    //плавное мигание (R, G, B, период, мин. яркость, частота обновления)
void smoothBlinking(colors* color, uint16_t period = 1000, uint8_t framerate = 200);      //плавное мигание (цвет из структуры, период, мин. яркость, частота обновления)
void gradient(uint8_t r, uint8_t g, uint8_t b, uint8_t r0, uint8_t g0, uint8_t b0, uint8_t speedGradient = 100, uint8_t step = 1);    //градиент (R1, G1, B1, R2, G2, B2, скорость, шаг)
void gradient(colors* color, colors* color0, uint8_t speedGradient = 100, uint8_t step = 1);    //градиент (цвет из структуры 1, цвет из структуры 2, скорость, шаг)
```
## константы
```
GENERAL_ANODE      //диод с общим анодом
GENERAL_CATHODE    //диод с общим катодом
```
## цвета
```
RED          (#FF0000)
ORANGE       (#FF7F00)
YELLOW       (#FFFF00)
SPRING_GREEN (#7FFF00)
GREEN        (#00FF00)
TURQUOISE    (#00FF7F)
CYAN         (#00FFFF)
OCEAN        (#007FFF)
BLUE         (#0000FF)
VIOLET       (#7F00FF)
MAGENTA      (#FF00FF)
RASPBERRY    (#FF007F)

WHITE        (#FFFFFF)
GRAY         (#7F7F7F)
BLACK        (#000000)
```

Примеры находятся в папке [examples](https://github.com/Arduino15/A15RGB/tree/main/examples).

## обратная связь
Если возникнут вопросы пишите в [чат](https://t.me/Arduino15Chat) или [мне](mailto:ardbazin@gmail.com)!

