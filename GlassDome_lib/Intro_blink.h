/*
  Intro_blink.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/
#ifndef Intro_blink_h
#define Intro_blink_h

#include "Arduino.h"

class Intro_blink
{
  public:
	Intro_blink(int pin);
	void _setup();
    
  private:
    int _count;
	int _pin;
	
};

#endif