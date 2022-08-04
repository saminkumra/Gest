//BleHID.ino
#include "BleHID.h"
#include "battery.h"
#include "sensors.h"
//#include "hardware_defs.h"

void bleInit(){
  #ifdef SERIAL_DEBUG
    Serial.println("Starting BLE");
  #endif
  
  //bleMouse.begin();
  Keyboard.begin();
  Mouse.begin();
  //bleMouse.setBatteryLevel(50);
}

void bleTask(){
  if(Keyboard.isConnected()){
    
    /*
    if(flex > threshold){
      Keyboard.press('6');
    } else {
      Keyboard.release('6');
    }
    */
    
  }
}
