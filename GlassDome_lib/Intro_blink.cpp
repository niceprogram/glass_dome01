/*
  Intro_blink.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Intro_blink.h"

Intro_blink::Intro_blink(int pin)
{
  //pinMode(pin, OUTPUT);
  _pin = pin;
}


// //-----------Arduino system startup indicator
void Intro_blink::_setup()
{
  for (_count = 0; _count < 3; _count++) {
    delay(200);
    digitalWrite(_pin, HIGH);
    delay(200);
    digitalWrite(_pin, LOW);
  }
  for (_count = 0; _count < 10; _count++) {
    delay(100-_count*2);
    digitalWrite(_pin, HIGH);
    delay(100-_count*3);
    digitalWrite(_pin, LOW);
  }
}

