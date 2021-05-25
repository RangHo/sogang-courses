#include <Arduino.h>
#include <math.h>

/*
CDS의 값과 반비례해서 5번핀에 연결된 LED 의 밝기가 변합니다.
또한, 초음파센서의 값에 따라서 LED 의 색과 버저의 주기가 변합니다.
초음파센서를 통해서 측정한 거리 또한 FND에 표시됩니다.
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

const int pin[8] = {36, 37, 38, 39, 40, 41, 42, 43};
const int com[4] = {28, 29, 30, 31};
//--------------------------------------------------
const int digits[10][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {1, 1, 1, 1, 0, 1, 1, 0}, // 9
};
//-----------millis()사용을 위한 값들-----------------
unsigned long current = 0;
unsigned long previous1 = 0;
unsigned long previous2 = 0;
unsigned long previous3 = 0;

bool buzz1 = 0;
bool buzz2 = 0;
bool buzz3 = 0;
//--------------------------------------------------
int cdsval = 0;
int ledval = 0;

float prevval = 0;

int buzzmode = 0;
//--------------------------------------------------
float sensor();
void allledoff();
void segments();
void ledctrl();
void buzzer();
//==================================================
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledr, OUTPUT);

  for (int i = 0; i < 8; i++)
  {
    pinMode(pin[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++)
  {
    pinMode(com[i], OUTPUT);
  }

  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(com[i], HIGH);
  }
}
//==================================================
void loop()
{
  cdsval = analogRead(cds);
  ledval = map(cdsval, 0, 1023, 0, 255);
  ledval = 255 - ledval;
  analogWrite(led1, ledval);

  if (cdsval < 700)
  {
    ledctrl();
    buzzer();
    segments();
  }

  if (cdsval >= 700)
  {
    allledoff();
    noTone(buzz);
  }
}
//==================================================
float sensor()
{ //초음파센서에서 값을 읽는 함수.
  float duration, distance;

  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  return (distance);
}
//==================================================
void ledctrl()
{ //거리에 따라서 LED와 버저를 조절하는 함수.
  float distance = sensor();

  allledoff(); // 모든 LED를 끔.

  if (abs(prevval - distance) > 7)
  { //거리가 급속도로 변하는지 판단.
    digitalWrite(ledg, 1);
    delay(100);
    digitalWrite(ledg, 0);
    digitalWrite(ledy, 1);
    delay(100);
    digitalWrite(ledy, 0);
    digitalWrite(ledr, 1);
    delay(100);
    digitalWrite(ledr, 0);
  }
  else if (distance < 10)
  {
    digitalWrite(ledr, 1);
    buzzmode = 1;
  }
  else if (distance >= 10 && distance < 20)
  {
    digitalWrite(ledy, 1);
    buzzmode = 2;
  }
  else if (distance >= 20)
  {
    digitalWrite(ledg, 1);
    buzzmode = 3;
  }
  prevval = distance;
}
//==================================================
void allledoff()
{ //모든 LED를 끄는 함수.
  digitalWrite(ledr, 0);
  digitalWrite(ledy, 0);
  digitalWrite(ledg, 0);
}
//==================================================
void segments()
{ //7-세그먼트에 값을 표시하는 함수.
  float integer, decimal;
  float value = sensor();

  decimal = modff(value, &integer);
  decimal *= 100;

  int num1 = static_cast<int>(integer) / 10; //FND 첫째 수. 정수부분의 십의자리.
  int num2 = static_cast<int>(integer) % 10; //FND 둘째 수. 정수부분의 일의자리.
  int num3 = static_cast<int>(decimal) / 10; //FND 셋째 수. 소수 첫째자리.
  int num4 = static_cast<int>(decimal) % 10; //FND 넷째 수. 소수 둘째자리.

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(com[j], HIGH);
    }

    switch (i)
    {
    case 0:
      for (int num = 0; num < 8; num++)
      { //FND-1
        digitalWrite(pin[num], digits[num1][num]);
      }
      break;

    case 1:
      for (int num = 0; num < 8; num++)
      { //FND-2
        digitalWrite(pin[num], digits[num2][num]);
      }
      digitalWrite(pin[7], 1); //소숫점
      break;

    case 2:
      for (int num = 0; num < 8; num++)
      { //FND-3
        digitalWrite(pin[num], digits[num3][num]);
      }
      break;

    case 3:
      for (int num = 0; num < 8; num++)
      { //FND-4
        digitalWrite(pin[num], digits[num4][num]);
      }
      break;

    default:
      break;
    }
    digitalWrite(com[i], LOW);
    Serial.println(sensor()); //디버깅용 시리얼
  }
}
//==================================================
void buzzer()
{                           //버저 삐삐거리는 함수.
  unsigned long smol = 100; // 울리는 간격들.
  unsigned long med = 200;
  unsigned long loong = 300;

  current = millis(); //세그먼트의 표기에 영향을 주지 않게하기 위해서 millis() 를 사용함.

  if (current - previous1 > smol)
  { //단거리 삑삑
    previous1 = current;

    if (buzz1 == 0)
    {
      buzz1 = 1;
      if (buzzmode == 1)
      {
        tone(buzz, 880);
      }
    }
    else
    {
      buzz1 = 0;
      noTone(buzz);
    }
  }

  if (current - previous2 > med)
  { //중거리 삑삑
    previous2 = current;

    if (buzz2 == 0)
    {
      buzz2 = 1;
      if (buzzmode == 2)
      {
        tone(buzz, 660);
      }
    }
    else
    {
      buzz2 = 0;
      noTone(buzz);
    }
  }

  if (current - previous3 > loong)
  { //장거리 삑삑
    previous3 = current;

    if (buzz3 == 0)
    {
      buzz3 = 1;
      if (buzzmode == 3)
      {
        tone(buzz, 550);
      }
    }
    else
    {
      buzz3 = 0;
      noTone(buzz);
    }
  }
}