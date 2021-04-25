#include <Arduino.h>
//--------------
const byte buttonPin = 2;
const byte ledPin = 13;
bool buttonState;
//--------------

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
   buttonState = digitalRead(buttonPin);
  delay(100);
  if(buttonState == HIGH) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  }

