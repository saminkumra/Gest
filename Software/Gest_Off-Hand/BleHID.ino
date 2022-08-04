//BleHID.ino
#include "BleHID.h"
#include "sensors.h"
#include "battery.h"

typedef std::array<bool, FLEX_QTY + 1> msk;

// from bit 1 to bit 5, left pinkie to left thumb
// bit 0 is selective and determined based on command

// movement set keys and gen commands
std::map<msk, const uint8_t> game1 { 
    {{1, 0, 0, 0, 0, 1}, KEY_RIGHT_ARROW},
    {{1, 1, 0, 0, 0, 0}, KEY_LEFT_ARROW},
    {{1, 0, 0, 0, 1, 0}, KEY_UP_ARROW},
    {{1, 1, 0, 0, 0, 1}, KEY_DOWN_ARROW},
    {{0, 1, 0, 1, 1, 0}, KEY_LEFT_SHIFT}, 
    {{0, 1, 1, 1, 1, 0}, KEY_LEFT_CTRL}, 
   };

// movement set letters and modes
std::map<msk, String> game2 {  
    {{0, 0, 0, 0, 0, 1}, "d"},
    {{0, 1, 0, 0, 0, 0}, "a"},
    {{0, 0, 0, 0, 1, 0}, "w"},
    {{0, 1, 0, 0, 0, 1}, "s"},
    {{0, 0, 0, 1, 1, 0}, "game"},
    {{0, 1, 0, 0, 1, 0}, "swipe"},
    {{0, 1, 1, 1, 0, 0}, " "},
   };

// control vars
msk button = {0};
bool gameState = 0;
bool newGameState = 0;
int swipeGame = 1;
int numSwipes = 2;
String keyMd;
uint8_t clickMd = 0;

void bleInit(){
  #ifdef SERIAL_DEBUG
    Serial.println("Starting BLE");
  #endif

  bleKeyboard.begin();
}

void gameMode() {

  // TODO: here only for now
  Serial.println("\nGameState");

  // logic if we choose anything from modes dictionary  
  if (keyMd == "swipe") {
  // next round of letters, rolls over
    swipeGame += 1;
    if (swipeGame > numSwipes) {
      swipeGame = 1;
    }
    delay(200);
    Serial.println("swipeGame");
    // these buttons are universal
  } else if (game1.count(button)) {
    clickMd = game1[button];
    bleKeyboard.write(clickMd);
  } else if (keyMd == " ") {
    bleKeyboard.print(keyMd);
  } else {
    if (swipeGame == 1) {
      button[0] = 1;
      if (game1.count(button)) {
        clickMd = game1[button];
        bleKeyboard.write(clickMd);
      }
    } else if (swipeGame == 2) {
      if (game2.count(button)){
        keyMd = game2[button];
        bleKeyboard.print(keyMd);
      }
    }
  }
}

void bleTask(){

  if(bleKeyboard.isConnected()){
    // go through the trouble only if keyboard is connected
    bleKeyboard.releaseAll();
    
    // check which fingers are bent and which aren't based on a threshold  
    for (int i = 1; i <= FLEX_QTY; i++) {
      button[i] = flexVal[i - 1] < gameThres;
      // TODO: delete later
      Serial.print((String)"button" + i + ": " + button[i] + " ");
    }

    button[0] = 0;
    keyMd = "";
    
    // check if changing modes
    if (game2.count(button)){
      keyMd = game2[button];
      newGameState = (keyMd == "game");
    }
  
    if (newGameState) {
      gameState = !gameState;
      delay(200);
    }

    if (gameState) {
      gameMode();
    }
  }

}
