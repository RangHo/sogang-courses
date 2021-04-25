void setup() {
  Serial.begin(9600);
  for(int i=1;i<5;i++){
  Serial.println(i);
  delay(500);
  }
}

void loop() {
}
