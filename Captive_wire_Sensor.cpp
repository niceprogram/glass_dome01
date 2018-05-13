/*
  Captive_wire_Sensor.h - Library for GlassDome art works.
  Created by K_Van, May 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Captive_wire_Sensor.h"

Captive_wire_Sensor::Captive_wire_Sensor()
{
}


//============initiate Captive_wire_Sensor::send_pulse
// every 1/2 a second a the test_wire _pulse is set to HIGH, 
// if you touch the wire on the outside of the glass dome while the test wire is HIGH,
// the select menu for the LEDs or RGBs become active.

void Captive_wire_Sensor::send_pulse(int test_wire_pulse, int feel_Captive_wire, int Next_menu) {

	_test_wire_pulse = test_wire_pulse;
	_feel_Captive_wire = feel_Captive_wire;
	_Next_menu = Next_menu;
	 if (millis() - _tempsmillis >= 2000 && _CurrentTouch_Captive_wire_Sensor == 0) {
		_tempsmillis = millis();
		digitalWrite(_test_wire_pulse, HIGH);
		if (millis() - _tempsmacros >= 50) {
			_tempsmacros = micros();
			if (analogRead(_feel_Captive_wire) < 500) {
				_CurrentTouch_Captive_wire_Sensor = 1;
				digitalWrite(_test_wire_pulse, LOW);
				switch (_Next_menu) {
				case 1://LED menu
				extern void manual_LED_selector();
				break;
				case 2://RGB menu
				extern void manual_RGB_selector();
				break;
				}
			}
		}
	}
  digitalWrite(_test_wire_pulse, LOW);
  _CurrentTouch_Captive_wire_Sensor = 0;
  //return 0;
}

//============Captive_wire_Sensor::menu_buttons
// use the wire like buttons. Touch a wire and return a 1
// can only be used if Captive_wire_Sensor is initiated is send_pulse (_CurrentTouch_Captive_wire_Sensor = 1;)
// and the menu_buttons become inactive after 30 seconds (if not touched)
bool Captive_wire_Sensor::menu_button(int wire_pulse, int feel_wire, bool captive_wire_initiated) {
	_wire_pulse = wire_pulse;
	_feel_wire = feel_wire;
	_captive_wire_initiated = captive_wire_initiated;
	_time_now = millis();
	
//////// loop --> for 30 seconds  if there is an input;  reset the time
	digitalWrite(_wire_pulse, HIGH); //set the wire pulse on HIGH 
  
	while (millis() < _time_now + 5000  ) { //start the timer (30 seconds) ........AND (captive_wire_initiated == true)
		if ((micros()-_tempsmacros)>=50) {   // fill the Captive_wire_Sensor for 50microseconds and test the result
			_tempsmacros=micros();
			//Serial.println(analogRead(A3));
			if (analogRead(_feel_Captive_wire) < 500) {
				return true; 
			}
		_time_now = millis();
		}
	}
	return 0;
	digitalWrite(_test_wire_pulse, LOW);
}





