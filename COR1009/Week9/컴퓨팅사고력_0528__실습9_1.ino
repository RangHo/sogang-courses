#include <Arduino.h>

int address_row[8] = {9, 14, 8, 12, 1, 7, 2, 5};
int address_col[8] = {13, 3, 4, 10, 6, 11, 15, 16};
int patterns[8] = {0, 0x66, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0};

void setup()
{
  for (int p = 0; p < 8; p++)
  {
    pinMode(address_row[p] + 29, OUTPUT);
    pinMode(address_col[p] + 29, OUTPUT);
    digitalWrite(address_row[p] + 29, HIGH);
    digitalWrite(address_col[p] + 29, LOW);
  }
}

void loop()
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      digitalWrite(address_col[col] + 29, bitRead(patterns[row], 7 - col));
    }
    digitalWrite(address_row[row] + 29, LOW);
    delay(2);
    digitalWrite(address_row[row] + 29, HIGH);
  }
}