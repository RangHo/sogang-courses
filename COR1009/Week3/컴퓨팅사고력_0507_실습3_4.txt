//--------------
const int led = 13;
int deelay = 1000;
bool con = 1;
//--------------

void setup() {
Serial.begin(9600);
pinMode(led, OUTPUT);
}

void loop() {
while(con){
    for (int i = 1; i<= 10; i++){
        digitalWrite(led, 1);
        delay(deelay);
        digitalWrite(led, 0);
        delay(deelay);
    }
    con = 0;
}
}
