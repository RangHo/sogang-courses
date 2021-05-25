//--------------
const int LedPin = 9;
//--------------

void setup()
{
    pinMode(LedPin, OUTPUT);
}

void loop()
{
    for (int i = 0; i < 20; i++)
    {
        analogWrite(LedPin, i);
        delay(100);
    }
}