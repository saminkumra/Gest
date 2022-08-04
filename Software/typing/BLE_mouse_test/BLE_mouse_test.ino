#include <BleCombo.h>
using namespace std;

// https://github.com/blackketter/ESP32-BLE-Combo
// code for ESP32 Feather

// the "keys" in the lookup tables assume order of values corresponding to fingers from your point of view
// left pinkie to right pinkie (with extra bool at the beginning of the array, so the length of the key is numFLEX + 1)
// order of flex sensors in FLEX array should match
#define FLEXR A4, \
              A3, \
              A2, \
              A1, \
              A0

#define FLEXL A4, \
              A3 //etc

#define WINDOW_SIZE 5

// all flex sensors
const int numFLEX = 5;
int FLEX[numFLEX] = {FLEXR};

//typedef std::array<bool, numFLEX + 1> msk;
typedef std::array<bool, 10 + 1> msk;

// letters dictionary
std::map<msk, String> letters { 
    {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, "a"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, "b"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "c"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "d"},
    {{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "e"}, 
    {{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "f"}, 
    {{0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, "g"}, 
    {{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "h"},
    {{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "i"},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "j"},
    {{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, "k"},
    {{0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0}, "l"},
    {{0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, "m"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, "n"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, "o"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "p"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "q"},
    {{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "r"}, 
    {{1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "s"}, 
    {{1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, "t"}, 
    {{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "u"},
    {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "v"},
    {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "w"},
    {{1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, "h"},
    {{1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0}, "y"},
    {{1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, "z"}, 
   };

// numbers and special chars dictionaries
std::map<msk, String> numbers { 
    {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, "1"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, "2"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "3"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "4"},
    {{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "5"}, 
    {{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "6"}, 
    {{0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, "7"}, 
    {{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "8"},
    {{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "9"},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "0"},
    {{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, "."}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, ","}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "'"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "/"},
    {{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "\\"}, 
    {{1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "-"}, 
    {{1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, ";"}, 
    {{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "="},
    {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "["},
    {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "]"},
  };

std::map<msk, String> numbers2 { 
    {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, "!"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, "@"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "#"}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "$"},
    {{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "%"}, 
    {{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "^"}, 
    {{0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, "&"}, 
    {{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "*"},
    {{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "("},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, ")"},
    {{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, ">"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, "<"}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, "\""}, 
    {{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, "?"},
    {{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "|"}, 
    {{1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "_"}, 
    {{1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, ":"}, 
    {{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "+"},
    {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, "{"},
    {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "}"},
  };

// fn dictionaries
std::map<msk, const uint8_t> fxns { 
    {{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, KEY_F1}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, KEY_F2}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, KEY_F3}, 
    {{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, KEY_F4},
    {{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, KEY_F5}, 
    {{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1}, KEY_F6}, 
    {{0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, KEY_F7}, 
    {{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, KEY_F8},
    {{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, KEY_F9},
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, KEY_F10},
    {{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}, KEY_F11},
    {{0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0}, KEY_F12},
   };

// important shortcuts
std::map<msk, const uint8_t> specials { 
    {{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}, KEY_ESC}, 
    {{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, KEY_BACKSPACE}, 
    {{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, KEY_RETURN}, 
    {{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}, KEY_DELETE},
    {{0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1}, KEY_TAB}, 
    {{0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1}, KEY_CAPS_LOCK}, 
    {{0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, KEY_RIGHT_ARROW},
    {{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, KEY_LEFT_ARROW},
    {{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}, KEY_UP_ARROW},
    {{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, KEY_DOWN_ARROW},
   };

// important shortcuts
std::map<msk, String> specials2 { 
    {{0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, " "}, 
    {{0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}, "."},
    {{0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1}, "!"},
    {{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1}, ","},
    {{0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1}, "?"},
    {{0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, "fxn"},
    {{0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0}, "letters"},
    {{0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0}, "numbers"},
    {{0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1}, "swipe"},
   };

// game 1
std::map<msk, const uint8_t> game1 { 
    {{1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0}, KEY_LEFT_SHIFT}, 
    {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, KEY_LEFT_CTRL}, 
    {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, KEY_RIGHT_ARROW},
    {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, KEY_LEFT_ARROW},
    {{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, KEY_UP_ARROW},
    {{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, KEY_DOWN_ARROW},
   };

// game 2
std::map<msk, String> game2 { 
    {{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, "swipe"}, 
    {{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, " "}, 
    {{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, "d"},
    {{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "a"},
    {{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, "w"},
    {{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, "s"},
   };

// modes
std::map<msk, String> modes { 
    {{0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, "game"}, 
    {{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, "keyboard"},
};

// set pin numbers for sensor
const int mouseButton = FLEX[1];
const int zoomButton = FLEX[2];
const int zoomThresh = 1400;
const int zoomDirThreshUpper = 20;
const int zoomDirThreshLower = -5;
const int mouseThresh = 1300;

// typing thresholds
const int flexThres = 1500;
const int flexThres3 = 1900;
const int gameThres = 1600;
int responseDelay = 100;     // response delay of the mouse, in ms
int flexReadingMouse;
int flexReadingZoom;
int flexReadingKey;

//smoothing values 
int zoomIndex = 0;
int zoomValue = 0 ;
int zoomSum = 0 ;
int zoomReadings[WINDOW_SIZE];
int zoomAveraged = 0;

//ROC 
int oldZoomAverage = 0;
int zoomRoc[WINDOW_SIZE];
int zoomRocIndex = 0;
int zoomRocValue = 0; 
int zoomRocSum = 0; 
int zoomRocAveraged = 0; 

// keyboard
int keyVal[numFLEX];
bool clickState = 0;
bool gameState = 0;
bool newGameState = 0;
bool zoomState = 0;
bool keyState = 0;
bool newKeyState = 0;
bool caps = 0;
bool newCaps = 0;
String keyMd;
// 0-4 right thumb to pinkie
// 5-9 left thumb to pinkie
msk button = {0};
int swipeKey = 1;
int swipeGame = 1;
int numSwipes = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  for (int i = 0; i < numFLEX; i++) {
    pinMode(FLEX[i], INPUT);
  }
  Keyboard.begin();
  Mouse.begin();
}

void rightClick() {
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

void leftClick() {
  // if the mouse is not pressed, press it:
  if (!Mouse.isPressed(MOUSE_RIGHT)) {
    Mouse.press(MOUSE_RIGHT);
    }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
}

// TODO
void gameMode() {  
  // recalc with gameThres
  /*for (int i = 1; i <= numFLEX; i++) {
    button[i] = keyVal[i - 1] > gameThres;
    Serial.print((String)"button" + i + ": " + button[i] + " ");
  }*/

  // TODO: zero out 2nd half
/* for (int i = numFLEX; i >= numFLEX/2; i--) {
    button[i] = 0;
    Serial.print((String)"button" + i + ": " + button[i] + " ");
  }
  */
  Serial.println("\nGameState");
  button[0] = 0;
  
  String keyMd;
  if (game2.count(button)){
    keyMd = game2[button];
  }
  
  if (keyMd == "swipe") {
    // next round of letters, rolls over
      swipeGame += 1;
      if (swipeGame > numSwipes) {
        swipeGame = 1;
      }
      delay(200);
      Serial.println("swipeGame");
  }  

  if (swipeGame == 1) {
    button[0] = 1;
    if (game1.count(button)) {
      const uint8_t temp_spec = game1[button];
      Keyboard.press(temp_spec);
    }
  } else if (swipeGame == 2) {
    if (keyMd){
      Keyboard.println(keyMd);
    }
  }
}

void loop() {
  //smooth zoom value 
  zoomValue = analogRead(mouseButton);        // Read the next sensor value
  zoomRocSum = zoomRocSum - zoomRoc[zoomRocIndex];       // Remove the oldest entry from the sum
  zoomRocValue = (zoomValue - oldZoomAverage);        // Read the next sensor value
  oldZoomAverage = zoomValue;
  zoomRoc[zoomRocIndex] = zoomRocValue;           // Add the newest reading to the window
  zoomRocSum = zoomRocSum + zoomRocValue;                 // Add the newest reading to the sum
  zoomRocIndex = (zoomRocIndex+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  zoomRocAveraged = zoomRocSum / WINDOW_SIZE; 

  //set zoom direction 
  int zoomDir = 0; 
  if (zoomRocAveraged > zoomDirThreshUpper){
    //zoom out
    zoomDir = 2;
  }
  else if(zoomRocAveraged < zoomDirThreshLower){
    //zoom in
    zoomDir = 1; 
  }
  else{
    zoomDir = 0;
  }
  
  flexReadingZoom = analogRead(zoomButton);
  Serial.println("\nStart");

  // check the values we're reading from flex sensors
  for (int i = 0; i < numFLEX; i++) {
    keyVal[i] = analogRead(FLEX[i]);
    Serial.print((String)"F" + i + ": " + keyVal[i] + " ");
  }
  
  clickState = (zoomValue < mouseThresh);
  //zoomState = (flexReadingZoom < zoomThresh);

  // compare all sensor values for keyboard
  for (int i = 1; i <= numFLEX; i++) {
    button[i] = keyVal[i - 1] > flexThres;
    Serial.print((String)"button" + i + ": " + button[i] + " ");
  }
  
  if (modes.count(button)) {
    String temp = modes[button];
    newGameState = (temp == "game");
    newKeyState = (temp == "keyboard");
    Serial.print(temp);
  }
  
  // get in or out of key state
  if (newKeyState) {
    keyState = !keyState;
    delay(200);
  // get in or out of game state
  } else if (newGameState) {
    gameState = !gameState;
    delay(200);
  }
  
  if (Keyboard.isConnected()){
    Keyboard.releaseAll();
    
    if (keyState) {
      Serial.println("KeyState");
      
      if (specials.count(button)){
        const uint8_t temp_spec = specials[button];
        if (temp_spec == KEY_CAPS_LOCK) {
          newCaps = !newCaps;
        } else {
          Keyboard.press(temp_spec);
        }
      } else if (specials2.count(button)) {
        keyMd = specials2[button];
      }
      
      if (keyMd == "swipe") {
        // next round of letters, rolls over
          swipeKey += 1;
          if (swipeKey > numSwipes) {
            swipeKey = 1;
          }
          delay(200);
      } else if (keyMd == "fxn") {
        // last round of letters/special symbols
          if (fxns.count(button)){
            Keyboard.press(fxns[button]);
          }
      } else {
        if (newCaps) {
          caps = !caps;
          delay(200);
        }
  
        if (swipeKey == 1) {
          button[0] = 0;          
        } else if (swipeKey == 2) {
          button[0] = 1;
        }
        String temp_str;
        if (keyMd == "numbers") {
          if (caps) {
            if (numbers2.count(button)) {
              temp_str = numbers2[button];
            }
          } else {
            if (numbers.count(button)) {
              temp_str = numbers[button];
            }
          }
          Keyboard.println(temp_str);
        } else if (keyMd == "letters") {
          if (letters.count(button)) {
            temp_str = letters[button];
            if (caps) {
              transform(temp_str.begin(), temp_str.end(), temp_str.begin(), ::toupper);
            }
            Keyboard.println(temp_str);
          }
        }
      }
    }
    else if (gameState) {
      gameMode();
    }
    else if (zoomState){
      Serial.println("zoom"); 
      if(zoomDir == 1){
        Serial.println("Zoom in");
        Mouse.move(0,0,1);
      }
      else if (zoomDir == 2){
        Serial.println("Zoom out");
        Mouse.move(0,0,-1);
      }
     }
    else if (clickState) {
      rightClick();
    }
  }
  delay(200);
}
