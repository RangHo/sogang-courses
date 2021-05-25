//--------------
const int led = 13;
int f = 0;
float c = 0;
bool con = 1;
//--------------

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  while (con)
  {
    for (f = 0; f <= 100; f += 10)
    {
      c = 5.0 / 9.0 * (f - 32.0);
      Serial.print(f);
      Serial.print(" F = ");
      Serial.print(c);
      Serial.println(" C");
    }
    con = 0;
  }
}
