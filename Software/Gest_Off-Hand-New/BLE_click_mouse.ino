#include "BLE_click_mouse.h"
#define TYPING_MODE

void mouseClickInit() {
  Serial.println("Starting mouse click");
  for(int i = 0; i < 5; i++){
    flex_pressed[i] = false;
  }
}

void rightClick() {
  // if the mouse is not pressed, press it:
  if (!flex_pressed[3]) {
    Mouse.press(MOUSE_RIGHT);
    flex_pressed[3] = true;
    }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
}

void leftClick() {
  // if the mouse is not pressed, press it:
  if (!Mouse.isPressed(MOUSE_LEFT)) {
    Mouse.press(MOUSE_LEFT);
    }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
}

void clickMouseTask() {
  if(Keyboard.isConnected()) {
    
    #ifdef TYPING_MODE
    int flex0_val = analogRead(FLEX0);
    int flex1_val = analogRead(FLEX1);
    int flex2_val = analogRead(FLEX2);
    int flex3_val = analogRead(FLEX3);
    int flex4_val = analogRead(FLEX4);

    if(flex0_val <= flex0_min + 250){
      if(!flex_pressed[0]){
        flex_pressed[0] = true;
        Keyboard.press(' ');
      }
    } else {
      if(flex_pressed[0]){
        flex_pressed[0] = false;
        Keyboard.release(' ');
      }
    }

    if(flex1_val <= flex1_min + 500){
      if(!flex_pressed[1]){
        flex_pressed[1] = true;
        Keyboard.press('d');
      }
    } else {
      if(flex_pressed[1]){
        flex_pressed[1] = false;
        Keyboard.release('d');
      }
    }

    if(flex2_val <= flex2_min + 500){
      if(!flex_pressed[2]){
        flex_pressed[2] = true;
        Keyboard.press('w');
      }
    } else {
      if(flex_pressed[2]){
        flex_pressed[2] = false;
        Keyboard.release('w');
      }
    }

    if(flex3_val <= flex3_min + 500){
      if(!flex_pressed[3]){
        flex_pressed[3] = true;
        Keyboard.press('a');
      }
    } else {
      if(flex_pressed[3]){
        flex_pressed[3] = false;
        Keyboard.release('a');
      }
    }

    if(flex4_val <= flex4_min + 500){
      if(!flex_pressed[4]){
        flex_pressed[4] = true;
        Keyboard.press('s');
      }
    } else {
      if(flex_pressed[4]){
        flex_pressed[4] = false;
        Keyboard.release('s');
      }
    }

    #endif

    #ifndef TYPING_MODE

    int left_click_val = analogRead(FLEX3);
    int right_click_val = analogRead(FLEX2);
    
//    if (left_click_val <= flex3_min + 500) {
//      Serial.println("Left Click!");
//      leftClick();
//    }
//    if (right_click_val <= flex2_min + 500) {
//      Serial.println("Right Click!");
//      rightClick();
//    }

    if(right_click_val <= flex2_min + 500){
      if(!flex_pressed[2]){
        flex_pressed[2] = true;
        Mouse.press(MOUSE_RIGHT);
      }
    } else {
      if(flex_pressed[2]){
        flex_pressed[2] = false;
        Mouse.release(MOUSE_RIGHT);
      }
    }

    if(left_click_val <= flex3_min + 500){
      if(!flex_pressed[3]){
        flex_pressed[3] = true;
        Mouse.press(MOUSE_LEFT);
      }
    } else {
      if(flex_pressed[3]){
        flex_pressed[3] = false;
        Mouse.release(MOUSE_LEFT);
      }
    }

    #endif
  }
}
