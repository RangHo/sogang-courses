#include <Arduino.h>

const int EN = 9;
const int MC1 = 2;
const int MC2 = 3;
const int POT = 0;

int val = 0;
int velocity = 0;

void forward(int rate);
void reverse(int rate);
void brake();

void setup()
{
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake();
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(POT);
  Serial.println(val);
  delay(100);
  if (val > 562)
  {
    velocity = map(val, 563, 1023, 0, 255);
    forward(velocity);
  }

  else if (val < 462)
  {
    velocity = map(val, 461, 0, 0, 255);
    reverse(velocity);
  }

  else
  {
    brake();
  }
}

void forward(int rate)
{
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
}