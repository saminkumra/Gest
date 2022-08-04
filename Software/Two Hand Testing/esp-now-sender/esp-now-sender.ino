#include "two_hand.h"

unsigned long tref = 100;
unsigned long tlen = 40;

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  two_hand_init();
  
}
 
void loop() {
  
  if(tref + tlen <= millis()){
    tref = millis();
    two_hand_loop();
  }
}
