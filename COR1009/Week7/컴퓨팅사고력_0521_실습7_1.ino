#include <Arduino.h>

const int CDS = 0;
const byte ledPin = 3;

int val = 0;
int intensity = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  val = analogRead(CDS);
  intensity = map(val, 0, 1023, 0, 255);
  Serial.print("Intensity : ");
  Serial.println(intensity);
  analogWrite(ledPin, intensity);
  delay(100);
}