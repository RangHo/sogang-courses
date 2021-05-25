void setup()
{
    Serial.begin(9600);
    int x = 2;
    int y = 6;
    Serial.println(x, BIN);
    Serial.println(y, BIN);
    Serial.println(x && y, BIN);
    Serial.println(x & y, BIN);
}
void loop()
{
}
