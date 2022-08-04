//hardware_defs.h

//#define REV0
#define REV1

/*
 * All the hardware related #define are placed within here
 */

#ifndef HARDWARE_DEFS_H
#define HARDWARE_DEFS_H

#ifdef REV0

#define FLEX0 25
#define FLEX1 25
#define FLEX2 26
#define FLEX3 27
#define FLEX4 27

#define BUTTON 33

#define LED1 13
#define LED2 14
#define LED3 18
#define LED4 19
#define LED5 23

#define BAT_SENSE 4
#define BAT_RATIO 2
#define VBUS_SENSE 17

#define FLEX_PULLDOWN 15 //no longer INPUT_PULLDOWN due to issues//tested to be 17.25+-0.25 kohms

#endif

#ifdef REV1

#define LED1 13
#define LED2 14
#define LED3 18
#define LED4 19
#define LED5 23

#define FLEX0 36
#define FLEX1 39
#define FLEX2 33
#define FLEX3 34
#define FLEX4 35

#define BUTTON 4

#define BAT_SENSE 32
#define BAT_RATIO 2
#define VBUS_SENSE 17 //digital

#define FLEX_PULLDOWN 15

#endif

#endif 
