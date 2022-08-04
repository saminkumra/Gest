//BleHID.ino
#include "BleHID.h"
#include "battery.h"

void bleInit(){
  #ifdef SERIAL_DEBUG
    Serial.println("Starting BLE");
  #endif
  
  bleMouse.begin();
  //bleMouse.setBatteryLevel(50);
}

void bleTask(){
  if(bleMouse.isConnected()){
    //bleMouse.move(0, 0, 0);
    //bleMouse.click(MOUSE_LEFT); 
  }
}
