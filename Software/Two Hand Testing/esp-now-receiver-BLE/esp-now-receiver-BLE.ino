#include "twoHandReceiver.h"
#include <BleKeyboard.h>
BleKeyboard bleKeyboard;

unsigned long tref = 100;
unsigned long tlen = 1000;
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  bleKeyboard.begin();
  twoHandReceiverInit();
}
 
void loop() {
  
  if(tref + tlen <= millis()){
    tref = millis();
    twoHandReceiverLoop();
    
    if(bleKeyboard.isConnected()) {
      bleKeyboard.print((int)myData.button);
    }
  }
}
