/*
  Captive_wire_Sensor.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/
#ifndef Captive_wire_Sensor_h
#define Captive_wire_Sensor_h

#include "Arduino.h"

class Captive_wire_Sensor
{
  public:
	Captive_wire_Sensor();
	
	void send_pulse(int test_wire_pulse, int feel_Captive_wire, int Next_menu );
	void manual_LED_selector();
	void manual_RGB_selector();
	
	bool menu_button(int wire_pulse, int feel_wire, bool captive_wire_initiated);
		
    
  private:
	long _tempsmillis =0;
	long _tempsmacros =0;
	int _CurrentTouch_Captive_wire_Sensor;
	int _test_wire_pulse;
	int _feel_Captive_wire;
	int _Next_menu;
	
	int _time_now;
	int _wire_pulse;
	int _feel_wire;
	bool _captive_wire_initiated;

};

#endif