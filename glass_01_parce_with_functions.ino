//============ PARCING
const byte numChars = 32;       // parcing
char receivedChars[numChars];   // parcing
char tempChars[numChars];       // temporary array for use when parsing

      // variables to hold the parsed data
char messageFrom_Bluetooth_Type[numChars] = {0};
float floatFromPC = 0.0;
boolean newData = false;

//============

//============ Motor PWM
int Motor_in_1;
int Motor_in_2;
//============ LED PWM
int LED_in_1;
int LED_in_2;


void setup() {
  pinMode(3, OUTPUT); /////////
  pinMode(5, OUTPUT); /////////
  pinMode(6, OUTPUT); //PWM ///
  pinMode(9, OUTPUT); /////////
  pinMode(11, OUTPUT);/////////
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  digitalWrite(11, LOW); 
  
  
  pinMode(13, OUTPUT);  // internal LED function blink
    
    

  blink(); // start the Arduino Pro mini ATMEGA 328P 3.3v
  Serial.begin(9600);
  Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
  Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
  Serial.println();
}

//============

void loop() {
    // parcing
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();  // Parce and execute FOUR functions (stepper, motor and lights)
        showParsedData();
        newData = false;
    }
}

//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============


void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFrom_Bluetooth_Type, strtokIndx); // copy it to messageFrom_Bluetooth_Type
    
    switch (messageFrom_Bluetooth_Type[0]) {
      case 'S': //tepperM
        Serial.println("StepperM");
        SteppeM();
        break;
        
      case 'P': // WM, 
        Serial.println("PWM_motor");
        PWM_Motor(); 
        break;  
        
      case 'L': // WM, 
        Serial.println("PWM_LED");
        PWM_LED(); 
        break; 
      
    }

    //strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    //integerFromPC = atoi(strtokIndx);     // convert this part to an integer

    //strtokIndx = strtok(NULL, ",");
    //floatFromPC = atof(strtokIndx);     // convert this part to a float

}



void showParsedData() {
    Serial.println("Message ");
    Serial.println(messageFrom_Bluetooth_Type);
 
}



//============Arduino systems startup indicator
void blink() {
  for (int count = 0; count < 5; count++) {
    delay(250);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    }
  }

//============SteppeM

void SteppeM() { //<Stepper, 1, 3, 255, 1>
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int SteppeM_No = atoi(strtokIndx);  
  Serial.println(("Stepper "+ String(SteppeM_No)));  // convert this part to an integer
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int Turns = atoi(strtokIndx); 
  Serial.println(("Turns "+ String(Turns)));
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int SteppeSpeed = atoi(strtokIndx); 
  Serial.println(("Speed "+ String(SteppeSpeed)));
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  bool ONOFFswitch = atoi(strtokIndx); 
  Serial.println(("Switch "+ String(ONOFFswitch)));
  
}

//============PWM_Motor

void PWM_Motor() {  //<PWM_Motor, 1, -1, 125, 1>
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int PWM_Motor_No = atoi(strtokIndx);  
  Serial.println(("PWM Motor # "+ String(PWM_Motor_No)));  // convert this part to an integer
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int Direction = atoi(strtokIndx); 
  Serial.println(("Direction "+ String(Direction)));
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int Motor_Speed = atoi(strtokIndx); 
  Serial.println(("Speed "+ String(Motor_Speed)));
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  bool ONOFFswitch = atoi(strtokIndx); 
  Serial.println(("ON or OFF "+ String(ONOFFswitch)));

  //There is space for two motors A and B
  switch (PWM_Motor_No) {
        case 1: 
          Serial.println("PWM Motor A, pins 3 and pin 5");
          Motor_in_1 = 3 ;
          Motor_in_2 = 5 ;
          break;
          
        case 2: 
          Serial.print("PWM Motor B pin 6 and 9");
          Motor_in_1 = 6 ;
          Motor_in_2 = 9 ;
          break;
  }
  //For Clock wise motion , in_1 = High , in_2 = Low

  if (Direction > 0) {
      digitalWrite(Motor_in_1, LOW);
      analogWrite(Motor_in_2, Motor_Speed);
    } else if (Direction < 0) {
      digitalWrite(Motor_in_2, LOW);
      analogWrite(Motor_in_1, Motor_Speed);
    } else if (ONOFFswitch == 0) {
      digitalWrite(Motor_in_1,LOW) ;
      digitalWrite(Motor_in_2,LOW) ;
    }
    
}



//============LED

void PWM_LED() {  //<LED, 1, 125, 1>
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int LED_No = atoi(strtokIndx);  
  Serial.println(("LED_No # "+ String(LED_No)));  // convert this part to an integer
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  int LED_pwm = atoi(strtokIndx); 
  Serial.println(("LED_PWM "+ String(LED_pwm)));
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  bool LED_ONOFFswitch = atoi(strtokIndx); 
  Serial.println(("ON or OFF "+ String(LED_ONOFFswitch)));

  //There is space for two motors A and B
  switch (LED_No) {
        case 1: 
          Serial.println("LED A pins 10");
          LED_in_1 = 10 ;
          break;
          
        case 2: 
          Serial.print("LED B pins 11");
          LED_in_1 = 11 ;
          break;
  }
  //For Clock wise motion , in_1 = High , in_2 = Low

  if (LED_ONOFFswitch == 1) {
      analogWrite(LED_in_1, LED_pwm);
    } else  {
      digitalWrite(LED_in_1,LOW) ;
    }
    
}
