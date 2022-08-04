//sensors.h
#ifndef SENSORS_H
#define SENSORS_H

/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
/***** GENERAL *****/
#include "config.h"
#include "hardware_defs.h"

/***** BNO055 *****/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* ~~~~~~~~~~ DEFINES ~~~~~~~~~~ */
/***** FLEX *****/
#define FLEX0_PIN FLEX0
#define FLEX1_PIN FLEX1
#define FLEX2_PIN FLEX2
#define FLEX3_PIN FLEX3
#define FLEX4_PIN FLEX4
#define FLEX_QTY 5

/* ~~~~~~~~~~ GLOBALS ~~~~~~~~~~ */
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);
int flex0_max, flex1_max, flex2_max, flex3_max, flex4_max;

/* ~~~~~~~~~~ STRUCTS ~~~~~~~~~~ */
/***** Flex *****/
struct flex_t{
  //Analog pin the flex sensor is connected to
  int pin = 0;
  //Number of ADC counts returned from flex sensor 
  int adcVal = 0;
  //Angle of flex on the flex sensor
  int flexAngle = 0;
  //Is a flex sensor connected at startup 
  int initPass = 0;

  //ADC count lower functional bound (12-bit ADC)
  const int adcLow = 2700;
  //ADC count upper functional bound (12-bit ADC)
  const int adcHigh = 1900;
  //Angle lower functional bound
  const int angleLow = 0; 
  //Angle upper functional bound
  const int angleHigh = 180;

  //Measure the number of ADC counts and put it in adcVal
  int measureAnalogPin(){
    adcVal = analogRead(pin);
    return adcVal;
  }

  //Measure the ADC pin, map it to an angle, and put it in flexAngle
  int measureFlex(){
    flexAngle = map(measureAnalogPin(), adcLow, adcHigh, angleLow, angleHigh);
    return flexAngle;
  }

   //Connect flex sensor object to pin 'input' and config as input
  void init(int input){
    pin = input;
    pinMode(pin, INPUT_PULLDOWN);
    if(measureAnalogPin() < (adcHigh * 1.2) && measureAnalogPin() > (adcLow * 0.8)){
      initPass = 1;
      #ifdef SERIAL_DEBUG
        Serial.println("Flex sensor detected!");
      #endif
    } else {
      #ifdef SERIAL_DEBUG
        Serial.println("Flex sensor not detected");
      #endif
    }
  }
  
} flex0, flex1, flex2, flex3, flex4;

/***** BNO055 *****/
struct lin_accel_t{
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
};

struct accel_t{
  //Does the BNO055 initialize successfully? 0 = NO, 1 = YES
  int initPass = 0;
  //Linear acceleration object
  lin_accel_t linearAccel;

  //Function for sampling the linear acceleration 
  void measureLinearAccel(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    linearAccel.x = euler.x();
    linearAccel.y = euler.y();
    linearAccel.z = euler.z();
  }
  
} bno055;

/* ~~~~~~~~~~ PROTOTYPES ~~~~~~~~~~ */
/***** Flex *****/
void flexInit();
void flexTask();

/***** BNO055 *****/
void accelInit();
void accelTask();

#endif
