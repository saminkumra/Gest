/**
 * This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.
 */
#include "BleMouse.h"
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define PIN_A 15
#define PIN_B 32
#define PIN_C 14
#define DELAY 100

BleMouse bleMouse;
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

float vel_x = 0.0;
float acc_x = 0.0;

struct timer{
  unsigned long ref;
  unsigned long delta;
  void update_ref(){
    ref = millis();
  }
} timer1, timer2;

struct mpu_t{
  float accel_x = 0.0;
  float accel_y = 0.0;
  float accel_z = 0.0;
} mpu1;

struct velocity_t{
  float x = 0.0;
  float y = 0.0;
} v1;

struct filter_t{
  unsigned long ref = 0;
  bool active = false;
  unsigned long timeout = 250;
} x_filter, y_filter;

struct button_t{
  int pin;
  bool prev_state = true;
  bool current_state = true;
  bool rising_edge = false;
  bool falling_edge = false;

  void init(int init_pin){
    pin = init_pin;
    pinMode(pin, INPUT_PULLUP);
  }

  void u(){
    prev_state = current_state;
    current_state = digitalRead(pin);
    
    if(prev_state != current_state){
      if(current_state){
        rising_edge = true;
      } else {
        falling_edge = true;
      }
    } else {
      rising_edge = false;
      falling_edge = false;
    }
  }
  
} button_a, button_b;

float accel_threshold = 0.5;
float accel_scalar = 50.0;

void setup() {
  Serial.begin(115200);

  //Begin BLE device
  Serial.println("Starting BLE");
  bleMouse.begin();

  //Begin BNO055 
  Serial.println("Starting BNO055");
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(500);

  bno.setExtCrystalUse(true);

  //Pin Setup
  button_a.init(PIN_A);
  button_b.init(PIN_B);
  
  pinMode(PIN_C, INPUT_PULLUP);

  //Begin Virtual Timers
  Serial.println("Starting Virtual Timers");
  timer1.ref = millis();
  timer1.delta = 5;
  timer2.ref = millis();
  timer2.delta = 10;
  
}

void loop() {
  if(bleMouse.isConnected()) {

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
        v1.x += accel_scalar*mpu1.accel_x * timer1.delta / 1000;
      }

      if(digitalRead(PIN_C) == LOW || (y_filter.active && (y_filter.ref + y_filter.timeout <= millis()))){
        v1.y = 0.0;
      } else {
        v1.y += accel_scalar*mpu1.accel_y * timer1.delta / 1000;
      }

      Serial.printf("Vx: %4.2f ", v1.x);
      Serial.printf("Vy: %4.2f ", v1.y);
      Serial.printf("Ax: %4.2f ", mpu1.accel_x);
      Serial.printf("Ay: %4.2f ", mpu1.accel_y);
      Serial.println("");
      
    }

    //BLE Virtual Timer
    if(timer2.ref + timer2.delta <= millis()){
      timer2.update_ref();

      bleMouse.move(v1.x, v1.y, 0);

      button_a.u();
      button_b.u();
      
      if(button_a.falling_edge){
        bleMouse.click(MOUSE_LEFT);
      }
      if(button_b.falling_edge){
        bleMouse.click(MOUSE_RIGHT);
      }
    }
  }
}
