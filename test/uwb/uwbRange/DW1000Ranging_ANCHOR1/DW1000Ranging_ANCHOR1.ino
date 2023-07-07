/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsAnchor
 *  - give example description
 */
#include <SPI.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "DW1000Ranging.h"

//---- connection pins (Xiao rp2040)
//const uint8_t PIN_RST = 7; // reset pin
//const uint8_t PIN_IRQ = 28; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin

//---- connection pins (Arduino Nano V3)
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

//---- display

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO


//Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/*
//-----
void init_display()
{
    display.begin(i2c_Address, true); // Address 0x3C default
    //display.setContrast (0); // dim display
  
    display.display();
    delay(2000);

    // Clear the buffer.
    display.clearDisplay();  

    // text display tests
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  //----
  display.println("UWB anchor");

}

*/
//-----
void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println(F("DW1000 Anchor setup ..."));
  Serial.print("PIN_SS :"); Serial.println(PIN_SS);

  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachBlinkDevice(newBlink);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  

// general configuration
  if(true)
  {
    DW1000.newConfiguration();
    Serial.println(F("setDefaults() ..."));
    DW1000.setDefaults();
    delay(5);
  }

    Serial.println(F("setDefaults() done"));
    DW1000.setDeviceAddress(6);
    DW1000.setNetworkId(10);
    DW1000.enableMode(DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
    DW1000.commitConfiguration();
    Serial.println(F("Config committed, devAddr=6, netId=10 ..."));
    //we start the module as an anchor
    DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

  //----
  delay(2);
  //---
  // DEBUG chip info and registers pretty printed
  char msg[128];
  if(true)
  {
    Serial.println(F("Read back settings...."));
    DW1000.getPrintableDeviceIdentifier(msg);
    Serial.print("Device ID: "); Serial.println(msg);
    DW1000.getPrintableExtendedUniqueIdentifier(msg);
    Serial.print("Unique ID: "); Serial.println(msg);
    DW1000.getPrintableDeviceMode(msg);
    Serial.print("Device mode: "); Serial.println(msg);
  }
  //---- display info
  /*
  if(true)
  {
    init_display();

  
    DW1000.getPrintableNetworkIdAndShortAddress(msg);
    Serial.print("Network ID & Device Address: "); 
    Serial.println(msg);
    
    Serial.print("NetID & DevAddr"); 
    display.println(msg);
  }
  */
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
}

void newBlink(DW1000Device* device) {
  Serial.print("blink; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

