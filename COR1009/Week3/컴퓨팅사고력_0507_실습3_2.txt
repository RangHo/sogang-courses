void setup() {
Serial.begin(9600);
}

void loop() {
char ch = Serial.read();
switch (ch) {
  case 'a':
    Serial.print('A');
    break;
  case 'b':
    Serial.print('B');
    break;  
  }
}
