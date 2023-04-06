/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <DW1000.h>


// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

// DEBUG packet sent status and count
boolean sent = false;
volatile boolean sentAck = false;
volatile unsigned long delaySent = 0;
int16_t sentNum = 0; // todo check int type
DW1000Time sentTime;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //-----
 // initialize the driver
  delay(2000);
  DW1000.begin(PIN_IRQ, PIN_RST);
  DW1000.select(PIN_SS);
  char sId[128]; sId[0]='\0';
  char sUid[128];sUid[0]='\0';
  
  DW1000.getPrintableDeviceIdentifier(sId);
  DW1000.getPrintableExtendedUniqueIdentifier(sUid);
  Serial.println(F("DW1000 initialized ..."));
  Serial.printf("Id='%s'\n" , sId);    
  Serial.printf("Uid='%s'\n", sUid);    
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  //Serial.print("Led High\n");
  delay(100);                      // wait for a second


  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  //Serial.print("Led Low\n");
  delay(100);                      // wait for a second
}
