const int PO3 = 3;
const int PI0 = A0;

void setup()
{
  pinMode(PO3, OUTPUT);
  pinMode(PI0, INPUT);
  Serial.begin(9600);
  analogWrite(PO3, 192);
}

void loop()
{

  Serial.println(analogRead(PI0) / 1023.0 * 5);
}