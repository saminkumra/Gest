//battery.h
#ifndef BATTERY_H
#define BATTERY_H

/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
#include "hardware_defs.h"

/* ~~~~~~~~~~ DEFINES ~~~~~~~~~~ */
#define VBAT_SENSE_PIN BAT_SENSE

/* ~~~~~~~~~~ STRUCTS ~~~~~~~~~~ */
struct battery_t{
  //Measured battery voltage ADC counts 
  int adcVal = 0;
  //Battery voltage 
  float voltage = 0.0;
  //Battery percentage
  int percent = 0;

  const int vLow = 330;
  const int vHigh = 420;
  const int pLow = 0;
  const int pHigh = 100;

  float measureVoltage(){
    adcVal = analogRead(VBAT_SENSE_PIN);
    voltage = ((float)adcVal)*BAT_RATIO*3.3/4096.0;
    return voltage;
  }

  int measurePercent(){
    percent = map((int)(100*measureVoltage()), vLow, vHigh, pLow, pHigh);
    return percent;
  }
  
} bat;

/* ~~~~~~~~~~ GLOBALS ~~~~~~~~~~ */
//int batTest;

/* ~~~~~~~~~~ PROTOTYPES ~~~~~~~~~~ */
void batteryInit();
void batteryTask();

#endif
