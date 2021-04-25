#include <Arduino.h>

/*
CDS의 값과 반비례해서 5번핀에 연결된 LED 의 밝기가 변합니다.
또한, 초음파센서의 값에 따라서 LED의 색과 버저의 주기가 변합니다.
*/


//------------------핀 설정-------------------------
const byte led1 = 5;
const byte ledg = 4;
const byte ledy = 3;
const byte ledr = 2;
const byte buzz = 6;

const byte cds = 0;
const byte trig = 12;
const byte echo = 11;
//--------------------------------------------------

int cdsval = 0;
int ledval = 0;

float prevval = 0;

float sensor();
void allledoff();
void ledctrl();

//==================================================
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledr, OUTPUT);
  Serial.begin(9600);
}
//==================================================
void loop() {
  cdsval = analogRead(cds);
  ledval = map(cdsval, 0, 1023, 0, 255);
  ledval = 255 - ledval;
  analogWrite(led1, ledval);

  if(cdsval < 700){
  ledctrl();
  //Serial.println(sensor()); //디버깅용 시리얼
  }

  if(cdsval >= 700){
    allledoff();
    }
}
//==================================================
float sensor(){
  float duration, distance;

  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034/2;

  return (distance);
}
//==================================================
void ledctrl(){
  float distance = sensor();

  allledoff(); // 모든 LED를 끔.

  if (abs(prevval - distance) > 7){ //거리가 급속도로 변하는지 판단.
    digitalWrite(ledg,1);
    delay(100);
    digitalWrite(ledg,0);
    digitalWrite(ledy,1);
    delay(100);
    digitalWrite(ledy,0);
    digitalWrite(ledr,1);
    delay(100);
    digitalWrite(ledr,0);
  }
  else if(distance < 10){ 
    digitalWrite(ledr,1);
    tone(buzz, 440, 100);
    delay(10);
  }
  else if(distance >= 10 && distance < 20){
    digitalWrite(ledy,1);
    tone(buzz, 440, 100);
    delay(150);
  }
  else if(distance >= 20){
    digitalWrite(ledg,1);
    tone(buzz, 440, 100);
    delay(200);
  }
  prevval = distance;
}
//==================================================
void allledoff(){
    digitalWrite(ledr,0);
    digitalWrite(ledy,0);
    digitalWrite(ledg,0);
} 