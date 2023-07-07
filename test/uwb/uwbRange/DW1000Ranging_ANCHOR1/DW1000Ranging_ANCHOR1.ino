/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsAnchor
 *  - give example description
 */
#include <SPI.h>
#include <Wire.h>
#include <ss_oled.h>
#include "DW1000Ranging.h"

//---- connection pins (Xiao rp2040)
//const uint8_t PIN_RST = 7; // reset pin
//const uint8_t PIN_IRQ = 28; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin

//---- connection pins (Arduino Nano V3)
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

//---- display-------------

// if your system doesn't have enough RAM for a back buffer, comment out
// this line (e.g. ATtiny85)
//#define USE_BACKBUFFER

#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

// Use -1 for the Wire library default pins
// or specify the pin numbers to use with the Wire library or bit banging on any GPIO pins
// These are the pin numbers for the M5Stack Atom default I2C
#define SDA_PIN 18 //21
#define SCL_PIN 19 //22
// Set this to -1 to disable or the GPIO pin number connected to the reset
// line of your display if it requires an external reset
#define RESET_PIN -1
// let ss_oled figure out the display address
#define OLED_ADDR -1
// don't rotate the display
#define FLIP180 0
// don't invert the display
#define INVERT 0
// Bit-Bang the I2C bus
#define USE_HW_I2C 0

// Change these if you're using a different OLED display
#define MY_OLED OLED_128x64
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
//#define MY_OLED OLED_64x32
//#define OLED_WIDTH 64
//#define OLED_HEIGHT 32

SSOLED ssoled;


//----------------------

//-----
void init_display()
{
    
      int rc;
  // The I2C SDA/SCL pins set to -1 means to use the default Wire library
  // If pins were specified, they would be bit-banged in software
  // This isn't inferior to hw I2C and in fact allows you to go faster on certain CPUs
  // The reset pin is optional and I've only seen it needed on larger OLEDs (2.4")
  //    that can be configured as either SPI or I2C
  //
  // oledInit(SSOLED *, type, oled_addr, rotate180, invert, bWire, SDA_PIN, SCL_PIN, RESET_PIN, speed)

  rc = oledInit(&ssoled, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L); // use standard I2C bus at 400Khz
    if (rc == OLED_NOT_FOUND)
    {
        Serial.print("OLED not found");
        return;
    }
    
    //----
    char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D"};
    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    oledSetBackBuffer(&ssoled, ucBackBuffer);
    delay(2000);
    

}


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
  
  if(true)
  {
    init_display();

  
    DW1000.getPrintableNetworkIdAndShortAddress(msg);
    Serial.print("Network ID & Device Address: "); 
    Serial.println(msg);
    
    oledFill(&ssoled, 0x0, 1);
   // oledWriteString(&ssoled, 0,16,0,(char *)"Hello UWB", FONT_NORMAL, 0, 1);
   // oledWriteString(&ssoled, 0,0,1,(char *)"NetID & DevAddr", FONT_SMALL, 1, 1);
    oledWriteString(&ssoled, 0,0,2,(char *)">", FONT_NORMAL, 0, 1);

    oledSetTextWrap(&ssoled, true);
    oledWriteString(&ssoled, 0,-1,-1,(char *)msg, FONT_SMALL, 1, 1);
//    oledWriteString(&ssoled, 0,0,3,(char*)"FL", FONT_LARGE, 0, 1);

  }
  
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

