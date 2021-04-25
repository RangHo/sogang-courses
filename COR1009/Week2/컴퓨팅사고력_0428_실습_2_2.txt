int intVal = 6;
char charVal = 65;

void setup() {
Serial.begin(9600);
Serial.print("intVal: ");
Serial.print(intVal);
Serial.print("  binary representation:");
Serial.println(intVal, BIN);

Serial.print("charVal: ");
Serial.println(charVal);
Serial.println(charVal, DEC);

Serial.println('A', DEC);
Serial.println(sizeof(intVal));

}

void loop() {
}
