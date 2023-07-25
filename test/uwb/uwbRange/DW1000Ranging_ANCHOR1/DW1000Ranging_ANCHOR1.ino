/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsAnchor
 *  - give example description
 */



#include <SPI.h>
#include <Wire.h>
#include <GyverOLED.h>
#include "DW1000Ranging.h"

//---- connection pins (Xiao rp2040)
//const uint8_t PIN_RST = 3; //7; // reset pin
//const uint8_t PIN_IRQ = 2; // 28; // irq pin
//const uint8_t PIN_SS = 7; //SS; // spi select pin

//---- connection pins (Esp32)
const uint8_t PIN_RST = 34; //7; // reset pin
const uint8_t PIN_IRQ = 35; // 28; // irq pin
const uint8_t PIN_SS = 33; //SS; // spi select pin

//---- connection pins (Arduino Nano V3)
//const uint8_t PIN_RST = 9; // reset pin
//const uint8_t PIN_IRQ = 2; // irq pin
//const uint8_t PIN_SS = SS; // spi select pin

//---- display-------------
GyverOLED<SSH1106_128x64> oled;

//----------------------

//-----
void init_display()
{
    oled.init();  // инициализация

  // --------------------------
  // настройка скорости I2C
  //Wire.setClock(800000L);   // макс. 800'000

  // --------------------------
  oled.clear();   // очистить дисплей (или буфер)
  oled.update();  // обновить. Только для режима с буфером! OLED_BUFFER

  // --------------------------
  oled.home();            // курсор в 0,0
  oled.print(F("Hello World!"));   // печатай что угодно: числа, строки, float, как Serial!
  oled.update();
  delay(2000);

  // --------------------------
  oled.setCursor(5, 1);   // курсор в (пиксель X, строка Y)
  oled.setScale(2);
  oled.print(F("UWB!"));
  oled.update();
  delay(2000);

}


//-----
void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println(F("DW1000 Anchor setup ..."));
  Serial.print(F("PIN_SS :")); Serial.println(PIN_SS);

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
    Serial.print(F("Device ID: ")); Serial.println(msg);
    DW1000.getPrintableExtendedUniqueIdentifier(msg);
    Serial.print(F("Unique ID: ")); Serial.println(msg);
    DW1000.getPrintableDeviceMode(msg);
    Serial.print(F("Device mode: ")); Serial.println(msg);
  }

  
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print(F("Network ID & Device Address: ")); 
  Serial.println(msg);

  //---- display info  
  if(true)
  {
    init_display();

  // --------------------------
    oled.setCursor(1, 3);   
    oled.setScale(1);
    oled.print(msg);

    oled.setCursor(1, 5);   
    oled.setScale(1);
    DW1000.getPrintableExtendedUniqueIdentifier(msg);
    oled.print(msg);



    oled.update();    

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
  Serial.print(F("blink; 1 device added ! -> "));
  Serial.print(F(" short:"));
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print(F("delete inactive device: "));
  Serial.println(device->getShortAddress(), HEX);
}

