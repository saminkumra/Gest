#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#define LED_PIN 13
//#define SERIAL_DEBUG
//23

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "fd7241d9-bd53-4b38-8b33-83921fc42837"
#define CHARACTERISTIC_UUID "aeb6cc01-48f4-483d-bf1e-f82f05be2ce4"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};



void setup() {
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  #endif
  pinMode(LED_PIN, OUTPUT);

  // Create the BLE Device
  BLEDevice::init("Gest Debug");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE 
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  //pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  #ifdef SERIAL_DEBUG
  Serial.println("Starting...");
  #endif
}

void loop() {
    // notify changed value
    if (deviceConnected) {

     uint8_t* myValue = pCharacteristic->getData();
      if(*myValue == 'y'){
        #ifdef SERIAL_DEBUG
        Serial.println("Pressed");
        #endif
        digitalWrite(LED_PIN, HIGH);
      } else if(*myValue == 'n'){
        #ifdef SERIAL_DEBUG
        Serial.println("Not Pressed");
        #endif
        digitalWrite(LED_PIN, LOW);
      } else {
        #ifdef SERIAL_DEBUG
        Serial.println("Error");
        #endif
        digitalWrite(LED_PIN, LOW);
      }
      //Serial.println(*myValue);
      delay(25);
      
//        pCharacteristic->setValue((uint8_t*)&value, 4);
//        pCharacteristic->notify();
//        value++;
//        delay(100); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        #ifdef SERIAL_DEBUG
        Serial.println("start advertising");
        #endif
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }

     
}
