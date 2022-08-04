#include "two_hand.h"

void two_hand_init(){
  
  // Set device as a Wi-Fi Station
  
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }


  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;


  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(USER_BUTTON, INPUT_PULLUP);
  myData.button = 0x00;
  //esp_sleep_enable_timer_wakeup(100000);
}

void two_hand_loop(){
  // Set values to send
//  if(digitalRead(USER_BUTTON)){
//    myData.button = 0x00;
//  } else {
//    myData.button = 0x01;
//  }
  myData.button++;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  
  //delay(1000);
  //Serial.println("Sleeping...");
  //delay(40);
  //esp_deep_sleep_start();
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
