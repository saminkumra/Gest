//sensors.c
#include "sensors.h"

void flexInit(){
  for (int i = 0; i < FLEX_QTY; i++) {
    flexArr[i].init(FLEX[i], flexMax[i], flexMin[i]);
  }
}

void flexTask(){
  // place in array for easy access
  for (int i = 0; i < FLEX_QTY; i++) {
    flexVal[i] = flexArr[i].measureFlex(flexMax[i], flexMin[i]);
  }
  #ifdef SERIAL_DEBUG
    Serial.printf("Flex: 0: %d \t 1: %d \t 2: %d \t 3: %d \t 4: %d \t\n", flexVal[0], flexVal[1], flexVal[2], flexVal[3], flexVal[4]);
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
      //Serial.printf("Accel: X: %4.2f \t Y: %4.2f \t Z: %4.2f \r\n", bno055.linearAccel.x, bno055.linearAccel.y, bno055.linearAccel.z);
    #endif
  }
}
