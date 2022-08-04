//sensors.c
#include "sensors.h"

void flexInit(){
  flex0.init(FLEX0_PIN);
  flex1.init(FLEX1_PIN);
  flex2.init(FLEX2_PIN);
  flex3.init(FLEX3_PIN);
  flex4.init(FLEX4_PIN);
}

void flexTask(){
  flex0.measureFlex();
  flex1.measureFlex();
  flex2.measureFlex();
  flex3.measureFlex();
  flex4.measureFlex();
  #ifdef SERIAL_DEBUG
    Serial.printf("Flex: 0: %d \t 1: %d \t 2: %d \t 3: %d \t 4: %d \t\n", flex0.measureFlex(), flex1.measureFlex(), 
    flex2.measureFlex(), flex3.measureFlex(), flex4.measureFlex());
  #endif
}

void accelInit(){

  //Check if the BNO055 is connected on I2C addr 0x28
  if(!bno.begin()){
    #ifdef SERIAL_DEBUG
      Serial.println("BNO055 not detected");
    #endif
  } else {
    #ifdef SERIAL_DEBUG
      Serial.println("BNO055 detected!");
    #endif
    bno055.initPass = 1;
  }

  //Give the BNO055 a second to start up 
  delay(1000);
  
}

void accelTask(){
  if(bno055.initPass){
    bno055.measureLinearAccel();
    #ifdef SERIAL_DEBUG
      Serial.printf("Accel: X: %4.2f \t Y: %4.2f \t Z: %4.2f \r\n", bno055.linearAccel.x, bno055.linearAccel.y, bno055.linearAccel.z);
    #endif
  }
}
