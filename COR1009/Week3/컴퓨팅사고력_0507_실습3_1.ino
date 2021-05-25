int t_on = 1000;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (t_on > 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(t_on);
    digitalWrite(LED_BUILTIN, LOW);
    delay(t_on);
  }
  else
  {
    t_on = 1000;
  }
}