/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "DW1000Ranging.h"


//---- connection pins (Arduino Nano V3)
//const uint8_t PIN_RST = 9; // reset pin
//const uint8_t PIN_IRQ = 2; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin

//---- connection pins (Esp32)
const uint8_t PIN_RST = 34; //7; // reset pin
const uint8_t PIN_IRQ = 35; // 28; // irq pin
const uint8_t PIN_SS = 33; //SS; // spi select pin

//------------------- OLED display -----------
/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
//--------------------------------------------
typedef Adafruit_SH1106G Display;
Display* l_pDisplay = nullptr;

void init_display(Display& display)
{
    if(l_pDisplay==nullptr) return;    
    display.begin(i2c_Address, true); // Address 0x3C default
    display.display();
    delay(2000);

    // Clear the buffer.
    display.clearDisplay();

    // text display tests
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Hello world");

    display.setTextSize(1);
    display.println("UWB Tag");

    display.display();
}

//--------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("DW1000 Tag setup ..."));

  //-------- OLED init
  l_pDisplay = new Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  auto& display = *l_pDisplay;
  delay(250); // wait for the OLED to power up

  init_display(display);
  //-------------------------------------

  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
// general configuration
  DW1000.newConfiguration();
  DW1000.setDefaults();
  DW1000.setDeviceAddress(6);
  DW1000.setNetworkId(10);

  DW1000.enableMode(DW1000.MODE_LONGDATA_RANGE_ACCURACY);
//DW1000.enableMode(DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
  
  DW1000.commitConfiguration();
  Serial.println(F("Committed configuration, devAddr=6, netId=10 ..."));

  //---
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000.getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000.getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);


  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

  // read back
  if(true)
  {
      Serial.println(F("Read back settings...."));
      char msg[128];
      DW1000.getPrintableDeviceIdentifier(msg);
      Serial.print("Device ID: "); Serial.println(msg);
      DW1000.getPrintableExtendedUniqueIdentifier(msg);
      Serial.print("Unique ID: "); Serial.println(msg);
      DW1000.getPrintableNetworkIdAndShortAddress(msg);
      Serial.print("Network ID & Device Address: "); Serial.println(msg);
      DW1000.getPrintableDeviceMode(msg);
      Serial.print("Device mode: "); Serial.println(msg);
      
      //------
      display.setTextSize(1);
      display.println(msg); // Network ID and Device address

      DW1000.getPrintableExtendedUniqueIdentifier(msg);
      display.setTextSize(1);
      display.println("Unique id:");
      display.println(msg);
      display.display();
  }
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  float r = DW1000Ranging.getDistantDevice()->getRange();
  Serial.print("\t Range: "); Serial.print(r); Serial.print(" m");
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  //----
  if(l_pDisplay!=nullptr)
  {
      auto& display = *l_pDisplay;

      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(4);

      display.print(r);
      display.println(" m");
      display.display();
      
  }
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

