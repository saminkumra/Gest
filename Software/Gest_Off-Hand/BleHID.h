//BleHID.h
#ifndef BLEHID_H
#define BLEHID_H

/* ~~~~~~~~~~ INCLUDES ~~~~~~~~~~ */
#include "BleKeyboard.h"
#include "config.h"

/* ~~~~~~~~~~ GLOBALS ~~~~~~~~~~ */
BleKeyboard bleKeyboard;

/* ~~~~~~~~~~ PROTOTYPES ~~~~~~~~~~ */
void bleInit();
void bleTask();

#endif
