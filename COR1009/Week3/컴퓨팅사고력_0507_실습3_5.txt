int sum = 0;
void setup() {
  Serial.begin(9600);
  for(int i=1;i<=50;i++){
  sum +=i;
  }
  Serial.print("1+2+...+50=");
  Serial.print(sum);
}

void loop() {
}
