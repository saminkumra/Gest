#include "twoHandReceiver.h"

unsigned long tref = 100;
unsigned long tlen = 40;
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  twoHandReceiverInit();
}
 
void loop() {
  if(tref + tlen <= millis()){
    tref = millis();
    twoHandReceiverLoop();
  }
}
