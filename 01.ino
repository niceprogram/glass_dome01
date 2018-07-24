//http://www.patorjk.com/software/taag/#p=display&h=3&v=0&f=Doom&t=Type%20Something%20

/////////////////////////////////
/////////
// _            _           _      
//(_)          | |         | |     
// _ _ __   ___| |_   _  __| | ___ 
//| | '_ \ / __| | | | |/ _` |/ _ \
//| | | | | (__| | |_| | (_| |  __/
//|_|_| |_|\___|_|\__,_|\__,_|\___|
//i                                
#include <Captive_wire_Sensor.h>
#include <Intro_blink.h>
#include <delayED.h>
#include "SoftPWM.h"
#include "FastLED.h"
#include <Thread.h>
#include <ThreadController.h>




// ThreadController, that will controll all threads
ThreadController controll = ThreadController();
Thread* Captive_menuThread = new Thread();
Thread PWM_MotorThread = Thread();
Thread PWM_fanThread = Thread();
Thread LED_7Thread = Thread();
Thread LED_8Thread = Thread();
Thread LED_9Thread = Thread();
Thread LED_10Thread = Thread();
Thread LED_11Thread = Thread();
Thread LED_12Thread = Thread();
Thread LED_13Thread = Thread();
Thread LED_A0Thread = Thread();
Thread LED_A1Thread = Thread();
Thread RGB_0Thread = Thread();
Thread RGB_1Thread = Thread();
Thread RGB_2Thread = Thread();
Thread RGB_3Thread = Thread();



// add more ... Thread hisThread = Thread();
//ThreadController groupOfThreads = ThreadController();


                               
/////////////////////////////////
/////////                              
//   _     _ _                            _ _                     
//  | |   (_| |                          (_| |                    
//  | |    _| |__  _ __ __ _ _ __ _   _   _| |_ ___ _ __ ___  ___ 
//  | |   | | '_ \| '__/ _` | '__| | | | | | __/ _ | '_ ` _ \/ __|
//  | |___| | |_) | | | (_| | |  | |_| | | | ||  __| | | | | \__ \
//  \_____|_|_.__/|_|  \__,_|_|   \__, | |_|\__\___|_| |_| |_|___/
//                                 __/ |                          
//                                |___/                   
// library intro Intro_blink.h
Intro_blink intro_blink(12); // A1analog_pins[A0 =14]

Captive_wire_Sensor Captive_LED_menu = Captive_wire_Sensor();  // pick the LEDs
Captive_wire_Sensor Captive_RGB_menu = Captive_wire_Sensor();  // change the colour scheme

// small delays
delayED delayLED = delayED(); // delay the 
delayED delayLoop = delayED();

/////////////////////////////////
/////////  
//  ______ _         _____      _               
//  | ___ (_)       /  ___|    | |              
//  | |_/ /_ _ __   \ `--.  ___| |_ _   _ _ __  
//  |  __/| | '_ \   `--. \/ _ | __| | | | '_ \ 
//  | |   | | | | | /\__/ |  __| |_| |_| | |_) |
//  \_|   |_|_| |_| \____/ \___|\__|\__,_| .__/ 
//                                       | |    
//                                       |_|    
/////////RGB pins///////////////
#define LED_PIN     2
#define NUM_LEDS    4
CRGBArray<NUM_LEDS> leds; 


/////////LED pins///////////////
uint8_t LED_pins [] = {7,8,10,11,12,13,A0,A1};  
int LED_grinder = 7;
int LED_axil = 8;
int LED_wheel = 10;
int LED_halfway_up = 11;
int LED_top = 12;
int LED_side_motor =13;
int LED_under_motor =A0;   
int LED_top_disk =A1;   
/////////////////////////////////
/////////
//   _____ _       _                  _   _            _       _     _      
//  |  __ | |     | |                | | | |          (_)     | |   | |     
//  | |  \| | ___ | |__   __ _ _ __  | | | | __ _ _ __ _  __ _| |__ | | ___ 
//  | | __| |/ _ \| '_ \ / _` | '__| | | | |/ _` | '__| |/ _` | '_ \| |/ _ \
//  | |_\ | | (_) | |_) | (_| | |    \ \_/ | (_| | |  | | (_| | |_) | |  __/
//   \____|_|\___/|_.__/ \__,_|_|     \___/ \__,_|_|  |_|\__,_|_.__/|_|\___|
//                                                                          
//   

//int CurrentTouch_Captive_wire_Sensor = 0; 
long tempsmacros = 0 ;
//long tempsmillis = 0 ;
long time_now =0;



/////////////////////////////////
/////////
//    __            _   _                 
//   / _|          | | (_)                
//  | |_ _   _  ___| |_ _  ___  _ __  ___ 
//  |  _| | | |/ __| __| |/ _ \| '_ \/ __|
//  | | | |_| | (__| |_| | (_) | | | \__ \
//  |_|  \__,_|\___|\__|_|\___/|_| |_|___/
//    

//============Captive_menu // activate the Captive menu
////////////////////////////////
////////////////////////////////                                    
void Captive_menu() { // activate the Captive menu
  int Active_LED_menu = Captive_LED_menu.hold_down(A2,A3,1000);
  if (Active_LED_menu == 17) { //play intro
    Serial.println("Active_LED_menu");
      manual_LED_selector_intro();
      manual_LED_selector();
    }        
}

//============manual_LED_selector_into --> after Captive_menu
////////////////////////////////
////////////////////////////////
void manual_LED_selector_intro() {
   ////////intro light sequence-> all the avialbe LED are lit up for a moment. 
  Serial.println("manual_LED_selector_Intro"); 
  /////indicates->manual_LED_selector active
  const int pin_count = sizeof(LED_pins) / sizeof(int);
  for (int _thisPin = 0; _thisPin < pin_count; _thisPin++ ) {  //light up the all the LEDs  Array = (LED_pins)
    
    SoftPWMSetPercent(LED_pins[_thisPin + 1],70) ; 
    SoftPWMSetPercent(LED_pins[_thisPin], 0);
    delayLED._delay(500);
  }
  delayLED._delay(500);
  //for (int thisPin = sizeof(LED_pins); thisPin > 0; ) {  //switch the LEDs off
  //  SoftPWMSetPercent(LED_pins[thisPin], 0);
  //  thisPin--;
  //  delay(500);
 // }
  //////// end of intro light sequence
}

//============manual_LED_selector--> after the manual_LED_selector_into
////////////////////////////////
////////////////////////////////
void manual_LED_selector() {
  delayED delay_intro;
  int _thisPin = 0;
  SoftPWMSetPercent(LED_pins[_thisPin], 80);
  
  while (1==1) {
    int val_Captive_LED_menu = Captive_LED_menu.touch_before_timesup(A2,A3,10000);
    if (val_Captive_LED_menu == 17) {
            Serial.println("yip wip"); 
            Pretty_LEDfade (_thisPin);
            _thisPin++;
            if ( _thisPin > sizeof(LED_pins)) {_thisPin=0;}
            Serial.println(_thisPin);
            SoftPWMSetPercent(LED_pins[_thisPin], 80);
            delayLoop._delay(500);
          } 
          else {
            Serial.println("LED_menu_stopped");
            for (int _thisPin = 0; _thisPin < sizeof(LED_pins); _thisPin++ ) {  //light up the all the LEDs  Array = (LED_pins)
              Pretty_LEDfade ( _thisPin);
            }
          val_Captive_LED_menu = 0;
          break;
          } 
  }
}
//============Pretty_LEDfade   fadeout of the LED in a pretty way
////////////////////////////////
////////////////////////////////
void Pretty_LEDfade (int _thisPin){
  delayED Pretty_;
  SoftPWMSetPercent(LED_pins[_thisPin], 10);
  Pretty_._delay(500);
  SoftPWMSetPercent(LED_pins[_thisPin], 50);
  Pretty_._delay(500);
  SoftPWMSetPercent(LED_pins[_thisPin], 0);
}





// // //-----------RGB_neopixel light up
////////////////////////////////
////////////////////////////////
void RGB_ON(int pixel_number) {
  leds[pixel_number] = CRGB(30, 30, 50);
  FastLED.show();
}


// // //-----------RGB_neopixel light off
void RGB_OFF(int pixel_number) {
  leds[pixel_number] = CRGB::Black;
  FastLED.show();
}


//============PWM_Motors
////////////////////////////////
////////////////////////////////
void PWM_Motor() {
  Serial.println("----------------------***--------PWM_Motor");
  int Motor_in_1 = 3 ;
  int Motor_in_2 = 5 ;

  digitalWrite(A7, HIGH);
  int _turnCheck =0;
  int _turnCheck_readout =0;
  int _sdelay = 500;

  //LED setup
  SoftPWMSetPercent(LED_under_motor, 10);
  SoftPWMSetPercent(LED_side_motor, 10);
  SoftPWMSetPercent(LED_top_disk, 10);
  SoftPWMSetPercent(LED_wheel, 10);
  SoftPWMSetPercent(LED_axil, 10);
  delayLED._delay(2000);
  int red_count ;
  int green_count ;
  int blue_count ;

  int _pixel_number = 3;
  unsigned long _hex =  0xFF008F;
  unsigned long _hex2 =  0xFFEE8F;
  leds[_pixel_number] = _hex;
  int _add_subR=1;
  int _add_subG=1;
  int _add_subB=1;
  FastLED.show();
  
  for (int _do_this_for_counts = 0; _do_this_for_counts < 2000; _do_this_for_counts++) { // do this loop for a 1000 times
    Serial.println(analogRead(A6));
    _turnCheck_readout = analogRead(A6);

    digitalWrite(Motor_in_2,LOW) ;
    SoftPWMSetPercent(Motor_in_1, 37); 
    
    
    SoftPWMSetPercent(LED_top_disk, 80);
    SoftPWMSetPercent(LED_wheel, 80);
    SoftPWMSetPercent(LED_axil, 80); 
    SoftPWMSetPercent(LED_under_motor, 20);
    SoftPWMSetPercent(LED_side_motor, 20);

        if (_turnCheck_readout < 20) { // if the read out is low, it might mean the wheel is not turning
          _turnCheck++;
          Serial.println("_turnCheck");
          Serial.print(_turnCheck);
        } else if ( 50 < _turnCheck_readout ) {
          _turnCheck=0;
        }

        ///// RGB
        red_count = red_count + 1*_add_subR;
        green_count = green_count + 1*_add_subG;
        blue_count = blue_count + 1*_add_subB;
        if (blue_count >= 250) { _add_subB =-1;        }
        if (green_count >= 750) { _add_subG =-1;      }
        if (red_count >= 500) {   _add_subR =-1;        }
        if (blue_count < 0) { _add_subB =1;        }
        if (green_count < 0) { _add_subG =1;      }
        if (red_count < 0) {   _add_subR =1;        }
        int red=map(red_count, 0, 500,75, 125);
        int green=map(green_count, 0, 750,75, 150);
        int blue=map(blue_count, 0, 250,10, 200);
        leds[_pixel_number] = CRGB(red, green, blue);
        
        FastLED.show();



        
        if (_turnCheck >= 25) { // the wheel is not turning fix it
          Serial.println("stuck");
          //leds[_pixel_number] = _hex2;
          //FastLED.show();
          //SoftPWMSetPercent(LED_under_motor, 5);
          SoftPWMSetPercent(LED_side_motor, 50);
          SoftPWMSetPercent(LED_top_disk, 15);
          //SoftPWMSetPercent(LED_wheel, 5);
          SoftPWMSetPercent(LED_axil, 5); 
          //activ jiggle menu
          digitalWrite(Motor_in_1,LOW) ;
          digitalWrite(Motor_in_2,HIGH) ;
          delayLoop._delay(300);  
          //leds[_pixel_number] = _hex;
          //FastLED.show();
          digitalWrite(Motor_in_2,LOW) ;
          digitalWrite(Motor_in_1,HIGH) ;
          delayLoop._delay(600);  
          _turnCheck=0;
        }  
  delayLoop._delay(100);   
  }
  Pretty_LEDfade(LED_under_motor);
  Pretty_LEDfade(LED_side_motor);
  Pretty_LEDfade(LED_top_disk);
  Pretty_LEDfade(LED_wheel);
  Pretty_LEDfade(LED_axil);
  SoftPWMSetPercent(Motor_in_1, 0); 
  digitalWrite(Motor_in_1,LOW) ;
  digitalWrite(Motor_in_2,LOW) ;
  digitalWrite(A7, LOW);
  RGB_OFF (3);
  Serial.println("----------------------END--------PWM_Motor");
}

//============PWM_fan
////////////////////////////////
////////////////////////////////
void  PWM_fan() {
  
  int _pin = 9;
  int _sdelay = 500;
  int _list[] = {1,1, 1,1, 1,1, 1,1, 1,1};
  const int _list_items = sizeof(_list) / sizeof(int);
  for (int _count = 0; _count < _list_items; ) {  //light up the all the LEDs  Array = (LED_pins)
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    SoftPWMSetPercent(_pin, 10);
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    Pretty_LEDfade(_pin);
  }
}

//============LED
////////////////////////////////
////////////////////////////////
void  LED_7() {//grinder
  int _pin = 7;
  int _sdelay = 500;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  LED_8() {//axis
  int _pin = 8;
  int _sdelay = 1500;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  LED_10() {//wheel
  int _pin = 10;
  int _sdelay = 2000;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  LED_11() {//middel rim
  int _pin = 11;
  int _sdelay = 2500;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  LED_12() {//high light
  
  int _pin = 12;
  int _list[] = {1,5};
  int _sdelay = 500;
  const int _list_items = sizeof(_list) / sizeof(int);
  for (int _count = 0; _count < _list_items; ) {  //light up the all the LEDs  Array = (LED_pins)
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    SoftPWMSetPercent(_pin, 80);
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    Pretty_LEDfade(_pin);
   }
}
void  LED_13() {//rotating disk
  int _pin = 13;
  int _list[] = {1,5};
  int _sdelay = 500;
  const int _list_items = sizeof(_list) / sizeof(int);
  for (int _count = 0; _count < _list_items; ) {  //light up the all the LEDs  Array = (LED_pins)
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    SoftPWMSetPercent(_pin, 80);
    delayLED._delay(_sdelay*(_list[_count]));
    _count++;
    Pretty_LEDfade(_pin);
   }
}
void  LED_A0() {//under motor
  int _pin = A0;
  int _sdelay = 4000;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  LED_A1() {//side motor
  int _pin = A1;
  int _sdelay = 5000;
  delayLED._delay(_sdelay);
  SoftPWMSetPercent(_pin, 80);
  delayLED._delay(_sdelay);
  delayLED._delay(_sdelay);
  Pretty_LEDfade(_pin);
}
void  RGB_0() {
  int _pixel_number = 0;
  unsigned long _hex =  0xFF007F;
  int _sdelay = 5000;
  delayLED._delay(_sdelay);
  leds[_pixel_number] = _hex;
  FastLED.show();
  delayLED._delay(_sdelay);
  RGB_OFF(_pixel_number);
  FastLED.show();
}
void  RGB_1() {
  int _pixel_number = 1;
  unsigned long _hex =  0xFF008F;
  int _sdelay = 5000;
  delayLED._delay(_sdelay);
  leds[_pixel_number] = _hex;
  FastLED.show();
  delayLED._delay(_sdelay);
  RGB_OFF(_pixel_number);
  FastLED.show();
}
void  RGB_2() {
  int _pixel_number = 2;
  unsigned long _hex =  0xFFD700;
  int _sdelay = 10000;
  delayLED._delay(_sdelay);
  leds[_pixel_number] = _hex;
  FastLED.show();
  delayLED._delay(_sdelay);
  RGB_OFF(_pixel_number);
  FastLED.show();
}
void  RGB_3() {
  int _pixel_number = 4;
  unsigned long _hex =  0xFF8C00;
  int _sdelay = 25000;
  delayLED._delay(_sdelay);
  leds[_pixel_number] = _hex;
  FastLED.show();
  delayLED._delay(_sdelay);
  RGB_OFF(_pixel_number);
  FastLED.show();
}

//              _     _            _                ___  
//             (_)   | |          | |              / \ \ 
//  __   _____  _  __| |  ___  ___| |_ _   _ _ __ | | | |
//  \ \ / / _ \| |/ _` | / __|/ _ | __| | | | '_ \| | | |
//   \ V | (_) | | (_| | \__ |  __| |_| |_| | |_) | | | |
//    \_/ \___/|_|\__,_| |___/\___|\__|\__,_| .__/| | | |
//                                          | |    \_/_/ 
//    

void setup() {
  Serial.begin(4800);
  ////////////////////////////
  /////////pins///////////////
  ////////////////////////////
  pinMode(3, OUTPUT); /////////
  pinMode(5, OUTPUT); /////////
  pinMode(6, OUTPUT); //PWM ///
  pinMode(9, OUTPUT); /////////
  
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  
 
  ////////////////////////////
  /////////LED pins/////////////// (see global LED_pins)
  ////////////////////////////
  SoftPWMBegin();
  for (int thisPin = 0; thisPin < sizeof(LED_pins); thisPin++) {
    SoftPWMSet(LED_pins[thisPin], 0);
  }
  SoftPWMSetFadeTime(ALL, 500, 1000);  // // Set fade time for ALL pins to 100 ms fade-up time, and 500 ms fade-down time
  

  
  pinMode(13, OUTPUT);  // internal LED function blink
  
  pinMode(A2, OUTPUT); //A2;////////////////////////////////
  digitalWrite(A2, LOW);//A2;/////////CapacitiveSensor//////
  pinMode(A3, INPUT);   //A3;///////////////////////////////
  
  pinMode(A7, OUTPUT);  /////////////////////////////////////////////////////
  digitalWrite(A7, LOW);//optical end stop//check if object is turning///////
  pinMode(A6, INPUT);   /////////////////////////////////////////////////////
  
  ////////////////////////////
  /////////RGBLED/////////////
  ////////////////////////////

  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //////////////////////////////////////////
  /////////prepare the Threads /////////////
  //////////////////////////////////////////  
  Captive_menuThread->onRun(Captive_menu);
  Captive_menuThread->setInterval(1500);
  int _intervaltime = 1500;
  Captive_menuThread->onRun(Captive_menu);
  Captive_menuThread->setInterval(_intervaltime); 
  
  PWM_MotorThread.onRun(PWM_Motor);
  PWM_fanThread.onRun(PWM_fan); 
  LED_7Thread.onRun(LED_7);
  LED_8Thread.onRun(LED_8);
  LED_10Thread.onRun(LED_10);
  LED_11Thread.onRun(LED_11); 
  LED_12Thread.onRun(LED_12);
  LED_13Thread.onRun(LED_13);
  LED_A0Thread.onRun(LED_A0);
  LED_A1Thread.onRun(LED_A1);
  RGB_0Thread.onRun(RGB_0);
  RGB_1Thread.onRun(RGB_1);
  RGB_2Thread.onRun(RGB_2);
  RGB_3Thread.onRun(RGB_3);
 

  PWM_MotorThread.setInterval(_intervaltime); 
  PWM_fanThread.setInterval(_intervaltime); 
  LED_8Thread.setInterval(_intervaltime); 
  LED_10Thread.setInterval(_intervaltime); 
  LED_11Thread.setInterval(_intervaltime); 
  LED_12Thread.setInterval(_intervaltime); 
  LED_13Thread.setInterval(_intervaltime); 
  LED_A0Thread.setInterval(_intervaltime); 
  LED_A1Thread.setInterval(_intervaltime); 
  RGB_0Thread.setInterval(_intervaltime); 
  RGB_1Thread.setInterval(_intervaltime); 
  RGB_2Thread.setInterval(_intervaltime); 
  RGB_3Thread.setInterval(_intervaltime); 

  
  controll.add(&PWM_MotorThread);
  controll.add(&PWM_fanThread); 
  controll.add(&LED_7Thread);
  controll.add(&LED_8Thread);
  controll.add(&LED_9Thread);
  controll.add(&LED_10Thread);
  controll.add(&LED_11Thread); 
  controll.add(&LED_12Thread);
  controll.add(&LED_13Thread);
  controll.add(&LED_A0Thread);
  controll.add(&LED_A1Thread);
  controll.add(&RGB_0Thread);
  controll.add(&RGB_1Thread);
  controll.add(&RGB_2Thread);
  controll.add(&RGB_3Thread);
 
  // controll.add(&hisThread); // & to pass the pointer to it

  
  ////////////////////////////
  /////////start up blink sequence/////////////
  ////////////////////////////
  //Serial.begin(9600);
  //cs_A2_A3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  
  Serial.println("startup indicator Blink a light");
  intro_blink._setup(); // //-----------Arduino system startup indicator with  blink on A1analog_pins[A0 =14]
  PWM_fan();
  RGB_ON(0);
  RGB_ON(1);
  RGB_ON(2);
  RGB_ON(3);
  SoftPWMSetFadeTime(3, 500, 1000);  // // Set fade time for ALL pins to 100 ms fade-up time, and 500 ms fade-down time
  SoftPWMSetFadeTime(5, 100, 100);  // // Set fade time for ALL pins to 100 ms fade-up time, and 500 ms fade-down time
  SoftPWMSetPercent(3, 0);
  PWM_Motor();
}
//              _     _   _                    ___  
//             (_)   | | | |                  / \ \ 
//  __   _____  _  __| | | | ___   ___  _ __ | | | |
//  \ \ / / _ \| |/ _` | | |/ _ \ / _ \| '_ \| | | |
//   \ V | (_) | | (_| | | | (_) | (_) | |_) | | | |
//    \_/ \___/|_|\__,_| |_|\___/ \___/| .__/| | | |
//                                     | |    \_/_/ 
//    
void loop() {
  Serial.println("loop");
  
  // run ThreadController
  // this will check every thread inside ThreadController,
  // if it should run. If yes, he will run it;
  //controll.run();
  //Captive_menu(); 
  //PWM_Motor(2,4);   // propeller on 
  //SoftPWMSetPercent(5, 50);
  //delayLoop._delay(1000);
  //SoftPWMSetPercent(5, 30);
  //delayLoop._delay(1000);
  //SoftPWMSetPercent(5, 50);
  //delayLoop._delay(1000);
  //PWM_Motor(2,-225);
  //delayLoop._delay(100);// propeller on 
  //PWM_Motor(2,0);   // propeller on 
  //delayLoop._delay(200);// propeller on 
  //PWM_Motor(2,3);   // propeller on 
  //SoftPWMSetPercent(5, 50);
  
  //PWM_Motor(1,175); //main motor on 
  //PWM_Motor(1,-254); //main motor on 

  //sunrise();
  
  //delayLoop._delay(10000);
  //PWM_Motor(2,6);   // propeller on 
  //PWM_Motor(1,-150); //main motor on 
  //Serial.println("done with captive menu");
  //delayLoop._delay(1000);
}



