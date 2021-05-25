#include <Arduino.h>

//--------------
const byte SPEAKER = 9;

int notes[] = {
    392, 392, 440, 440, 392, 392, 330};
int times[] = {
    250, 250, 250, 250, 250, 250, 500};
//--------------

void setup()
{
  for (int i = 0; i < 7; i++)
  {
    tone(SPEAKER, notes[i], times[i]);
    delay(times[i]);
  }
}

void loop()
{
}
