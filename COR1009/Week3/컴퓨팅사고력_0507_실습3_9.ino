//--------------
const int led = 13;
int blinkRate = 0;
//--------------

void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    Serial.println("Enter delay");
}

void blink()
{
    digitalWrite(led, 1);
    delay(blinkRate);
    digitalWrite(led, 0);
    delay(blinkRate);
}

void loop()
{
    if (Serial.available())
    {
        char ch = Serial.read();
        if (isDigit(ch))
        {
            blinkRate = (ch - '0');
            blinkRate *= 100;
            Serial.print("Rate = ");
            Serial.print(blinkRate);
            Serial.println("msec");
        }
        else
        {
            Serial.println("Enter value between 0 and 9.");
        }
    }
    blink();
}
