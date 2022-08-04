//battery.ino
#include "BleHID.h"
#include "battery.h"

void batteryInit(){
  pinMode(VBAT_SENSE_PIN, INPUT);
  //batTest = 0;
}

void batteryTask(){
  bat.measurePercent();
  #ifdef SERIAL_DEBUG
    Serial.printf("Battery: %d%%\r\n", bat.percent);
  #endif
  if(Keyboard.isConnected()){
    Keyboard.setBatteryLevel(bat.percent);
  }
}
