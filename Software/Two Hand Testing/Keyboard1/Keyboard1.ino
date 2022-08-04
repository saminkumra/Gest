/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(33, INPUT_PULLUP);
}

void loop() {
  if(bleKeyboard.isConnected()) {
//    Serial.println("Sending 'Hello world'...");
//    bleKeyboard.print("Hello world");
//
//    delay(1000);

    if(!digitalRead(33)){
      //Serial.println("Sending Enter key...");
      bleKeyboard.print("Hello World!");
      bleKeyboard.write(KEY_RETURN);
  
      delay(25);
    }
    

//    Serial.println("Sending Play/Pause media key...");
//    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
//
//    delay(1000);

   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    /*
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
  }

//  Serial.println("Looping...");
//  delay(40);
}
