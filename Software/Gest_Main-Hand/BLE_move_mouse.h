/**
 * This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.
 */
#ifndef BLE_MOVE_MOUSE_H
#define BLE_MOVE_MOUSE_H

//#include "BleMouse.h"
#include  <BleCombo.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "sensors.h"
#define PIN_A 15
#define PIN_B 32
#define PIN_C 14
#define DELAY 100


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
float x_accel_scalar = 50.0;
float y_accel_scalar = 25.0;

void bleMouseInit();

void mouseMoveTask();

#endif
