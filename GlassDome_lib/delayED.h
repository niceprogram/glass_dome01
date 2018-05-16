/*
 delayED.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/
#ifndef delayED_h
#define delayED_h

#include "Arduino.h"

class delayED
{
  public:
	delayED();
	
	void _delay(int delay_time);   
  
  private:
    int _time_now;
	//int _delay_time;
	
};

#endif