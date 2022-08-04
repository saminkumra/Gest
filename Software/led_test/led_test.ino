#include "hardware_defs.h"

/*
#define LED1 35
#define LED2 34
#define LED3 18
#define LED4 19
#define LED5 23
 */

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BAT_SENSE, INPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED5, HIGH);
  delay(100);

  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, LOW);
  delay(100);
  digitalWrite(LED3, LOW);
  delay(100);
  digitalWrite(LED4, LOW);
  delay(100);
  digitalWrite(LED5, LOW);
  delay(100);

  char bat_v = (((analogRead(BAT_SENSE) - (2.5 * (4095/2) / 3.3))/((4095/2)/3.3))/0.05);
  Serial.println((int)bat_v);
  digitalWrite(LED1, bat_v & 0b00000001);
  digitalWrite(LED2, bat_v & 0b00000010);
  digitalWrite(LED3, bat_v & 0b00000100);
  digitalWrite(LED4, bat_v & 0b00001000);
  digitalWrite(LED5, bat_v & 0b00010000);
  delay(1000);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
}
