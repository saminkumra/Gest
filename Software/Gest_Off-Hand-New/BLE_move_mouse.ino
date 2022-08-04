#include "BLE_move_mouse.h"

void bleMouseInit() {
  //Begin BLE device
  Serial.println("Starting BLE");
  Mouse.begin();
  
  //Begin BNO055 
  Serial.println("Starting BNO055");
  if(!bno.begin())
  {
    //There was a problem detecting the BNO055 ... check your connections 
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(500);

  bno.setExtCrystalUse(true);
  
  pinMode(PIN_C, INPUT_PULLUP);

  //Begin Virtual Timers
  Serial.println("Starting Virtual Timers");
  timer1.ref = millis();
  timer1.delta = 5;
  timer2.ref = millis();
  timer2.delta = 10;
  
}

void mouseMoveTask() {
  if(Keyboard.isConnected()) {

    //Accelerometer Virtual Timer
    if(timer1.ref + timer1.delta <= millis()){
      timer1.update_ref();
      
      imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

      mpu1.accel_x = euler.x();
      mpu1.accel_y = euler.y();

      if(abs(mpu1.accel_x) < accel_threshold){
        if(!x_filter.active) {
          x_filter.active = true;
          x_filter.ref = millis();
        }
      } else {
        x_filter.active = false;
      }

      if(abs(mpu1.accel_y) < accel_threshold){
        if(!y_filter.active) {
          y_filter.active = true;
          y_filter.ref = millis();
        }
      } else {
        y_filter.active = false;
      }

      if(digitalRead(PIN_C) == LOW || (x_filter.active && (x_filter.ref + x_filter.timeout <= millis()))){
        v1.x = 0.0;
      } else {
        v1.x -= x_accel_scalar*mpu1.accel_x * timer1.delta / 1000;
      }

      if(digitalRead(PIN_C) == LOW || (y_filter.active && (y_filter.ref + y_filter.timeout <= millis()))){
        v1.y = 0.0;
      } else {
        v1.y += y_accel_scalar*mpu1.accel_y * timer1.delta / 1000;
      }

//      Serial.printf("Vx: %4.2f ", v1.x);
//      Serial.printf("Vy: %4.2f ", v1.y);
//      Serial.printf("Ax: %4.2f ", mpu1.accel_x);
//      Serial.printf("Ay: %4.2f ", mpu1.accel_y);
//      Serial.println("");
      
    }

    //BLE Virtual Timer
    if(timer2.ref + timer2.delta <= millis()){
      timer2.update_ref();

      Mouse.move(v1.x, v1.y, 0);
    }
  }
}
