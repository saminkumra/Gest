#ifndef TWO_HAND_RECEIVER_H
#define TWO_HAND_RECEIVER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char button;
} struct_message;

// Create a struct_message called myData
struct_message myData;

uint8_t newMACAddress[] = {0x47, 0x65, 0x73, 0x74, 0x69, 0x69};

void twoHandReceiverInit();
void twoHandReceiverLoop();
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

#endif
