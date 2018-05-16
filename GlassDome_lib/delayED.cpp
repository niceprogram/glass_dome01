/*
  delayED.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "delayED.h"

delayED::delayED()
{
}



//============Soft delay 
// delay the script for an certain time. Like 'sleep' but using the timer 
void delayED::_delay(int delay_time) {
	_time_now = millis();
	while (millis() < _time_now + delay_time) {
	//;
    }
}

// HOWTO
// make an instance of delayED delayLED = delayED();
// use delayLED._delay([value]);  