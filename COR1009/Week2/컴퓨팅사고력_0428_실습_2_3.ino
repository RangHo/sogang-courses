int a = 10;
int b = 20;

void setup() {
Serial.begin(9600);
Serial.print("a="); Serial.print(a);
Serial.print(", b="); Serial.println(b);
Serial.print("a+b="); Serial.println(a+b);

Serial.print("a/b="); Serial.println(a/b);

Serial.print("10.0/20 = "); Serial.println(10.0/20);

float x = 10; float y=20;
Serial.print("x/y="); Serial.println(x/y);
}

void loop() {
}
