//#include "BleMouse.h"
#ifndef BLE_CLICK_MOUSE_H
#define BLE_CLICK_MOUSE_H

#include <BleCombo.h>
#include "sensors.h"
#include "hardware_defs.h"

using namespace std;

bool flex_pressed[5];


void mouseClickInit();
void rightClick();

void leftClick();

void clickMouseTask();

#endif
