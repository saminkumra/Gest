/*********************************
 * 
 * Gest - Main
 * Chris | Isabelle | Samin | Danche
 * Northwestern CE347 2022
 * 
 * REQUIRED INCLUDE LIBRARIES FOR COMPILE: 
 * Adafruit_Sensor.h
 * Adafruit_BNO055.h
 * 
 * TARGET BOARD:
 * WEMOS D1 MINI ESP32
 * If you do not target this board, all the pin defs will break!
 * 
 ********************************/

 #include "sensors.h"
 #include "timer.h"
 #include "config.h"
 #include "BleHID.h"
 #include "battery.h"
 #include "calibration.h"
 #include "button.h"

unsigned long calibration_mode = 10000;

void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(SERIAL_SPEED);
  #endif
  flexInit();
  accelInit();
  bleInit();
  batteryInit();
  button_setup();
  
  allTimersInit();
  
}


void loop() {
  
  if (!button_pressed()){
    for(int i = 0; i < FLEX_QTY; i++){
      flexMax[i] = 0;
      flexMin[i] = 2500;
    }
    unsigned long ref = millis();
    calibration_mode = ref + 10000;
  }
  if (millis() < calibration_mode) {
    calibration_setup();
    Serial.printf("new_flex0: %d,\t new_flex1: %d,\t new_flex2: %d,\t new_flex3: %d,\t new_flex4: %d\n", flexMax[0], flexMax[1], flexMax[2], flexMax[3], flexMax[4]);
    Serial.printf("flex0: %d,\t flex1: %d,\t flex2: %d,\t flex3: %d,\t flex4: %d\n", flexMin[0], flexMin[1], flexMin[2], flexMin[3], flexMin[4]);
  }
  if (millis() > calibration_mode) {
    if(locateTimer(&head, 1)->timer->bump()){
      flexTask();
    }
  
    if(locateTimer(&head, 2)->timer->bump()){
      accelTask();
    }
  
    if(locateTimer(&head, 3)->timer->bump()){
      bleTask();
    }
  
    if(locateTimer(&head, 4)->timer->bump()){
      batteryTask();
    }
  }
}
