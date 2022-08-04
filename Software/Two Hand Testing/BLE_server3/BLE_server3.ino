#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "fd7241d9-bd53-4b38-8b33-83921fc42837"
#define CHARACTERISTIC_UUID "aeb6cc01-48f4-483d-bf1e-f82f05be2ce4"

BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Gest Debug");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("0");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  uint8_t* myValue = pCharacteristic->getData();
  if(*myValue == 'y'){
    Serial.println("Pressed");
    digitalWrite(23, HIGH);
  } else if(*myValue == 'n'){
    Serial.println("Not Pressed");
    digitalWrite(23, LOW);
  } else {
    Serial.println("Error");
    digitalWrite(23, LOW);
  }
  //Serial.println(*myValue);
  delay(25);
}
