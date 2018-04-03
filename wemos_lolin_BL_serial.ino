HardwareSerial Serial2(2);

void setup() {
  Serial.begin(9600);
  //Serial2.begin(115200);  // put your setup code here, to run once:
  Serial2.begin(9600, SERIAL_8N2, 13, 15); //baud rate, 8 data bits - no parity - 2 stop bits, RX pin, TX pin
}

void loop() {

  Serial.println("usbserial");  // put your main code here, to run repeatedly:
  Serial2.println("UART2"); 
  delay(1000);
  }
