#include "hardware_defs.h"
#include "sensors.h"
 
void calibration_setup(){

  int flex0 = analogRead(FLEX0);
  int flex1 = analogRead(FLEX1);
  int flex2 = analogRead(FLEX2);
  int flex3 = analogRead(FLEX3);
  int flex4 = analogRead(FLEX4);
  if (flex0 < flex0_min) {
    flex0_min = flex0;
  }
  if (flex1 < flex1_min) {
    flex1_min = flex1;  
  }
  if (flex2 < flex2_min) {
    flex2_min = flex2;
  }
  if (flex3 < flex3_min) {
    flex3_min = flex3;
  }
  if (flex4 < flex4_min) {
    flex4_min = flex4;
  }

}
