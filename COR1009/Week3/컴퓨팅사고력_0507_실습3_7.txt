int a = 0;
void setup() {
    Serial.begin(9600);
}

int ex4(int a){
return 2+a;
} 

void loop() {
    a = ex4(3);
    Serial.println(a);
}