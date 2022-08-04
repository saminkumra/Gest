//BleHID.h
#ifndef BLEHID_H
#define BLEHID_H

/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
#include "BleMouse.h"
#include "config.h"

/* ~~~~~~~~~~ GLOBALS ~~~~~~~~~~ */
BleMouse bleMouse;

/* ~~~~~~~~~~ PROTOTYPES ~~~~~~~~~~ */
void bleInit();
void bleTask();

#endif
