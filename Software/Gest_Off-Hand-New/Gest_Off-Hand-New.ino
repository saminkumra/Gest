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
 #include "BLE_move_mouse.h"
 #include "BLE_click_mouse.h"

unsigned long calibration_mode = 10000;

void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(SERIAL_SPEED);
  #endif
  flexInit();
  //accelInit();
  bleInit();
  batteryInit();
  button_setup();
  //bleMouseInit();
  
  allTimersInit();
  
}


void loop() {
  
  if (!button_pressed()){
    flex0_min = 2500, flex1_min = 2500, flex2_min = 2500, flex3_min = 2500, flex4_min = 2500;
    unsigned long ref = millis();
    calibration_mode = ref + 10000;
  }
  if (millis() < calibration_mode) {
    calibration_setup();
    Serial.printf("new_flex0: %d,\t new_flex1: %d,\t new_flex2: %d,\t new_flex3: %d,\t new_flex4: %d\n", flex0_min, flex1_min, flex2_min, flex3_min, flex4_min);
  }
  if (millis() > calibration_mode) {
    if(locateTimer(&head, 1)->timer->bump()){
      flexTask();
    }
  
    if(locateTimer(&head, 2)->timer->bump()){
      //accelTask();
    }
  
    if(locateTimer(&head, 3)->timer->bump()){
      bleTask();
    }
  
    if(locateTimer(&head, 4)->timer->bump()){
      batteryTask();
    }
    
    if(locateTimer(&head, 5)->timer->bump()){
      clickMouseTask();
    }
//    if (analogRead(FLEX0) < flex0_min + 100) { 
//      mouseMoveTask();
//    }
  }
}
