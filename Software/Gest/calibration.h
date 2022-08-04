#include "hardware_defs.h"

 
void calibration_setup(){

  int flex0 = analogRead(FLEX0);
  int flex1 = analogRead(FLEX1);
  int flex2 = analogRead(FLEX2);
  int flex3 = analogRead(FLEX3);
  int flex4 = analogRead(FLEX4);
  if (flex0 > flex0_max) {
    flex0_max = flex0;
  }
  if (flex1 > flex1_max) {
    flex1_max = flex1;
  }
  if (flex2 > flex2_max) {
    flex2_max = flex2;
  }
  if (flex3 > flex3_max) {
    flex3_max = flex3;
  }
  if (flex4 > flex4_max) {
    flex4_max = flex4;
  }

}
