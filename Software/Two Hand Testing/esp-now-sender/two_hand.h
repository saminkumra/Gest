#ifndef TWO_HAND_H
#define TWO_HAND_H

#include <esp_now.h>
#include <WiFi.h>

#define USER_BUTTON 33

uint8_t broadcastAddress[] = {0x47, 0x65, 0x73, 0x74, 0x69, 0x69};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char button;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

void two_hand_init();
void two_hand_loop();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif
