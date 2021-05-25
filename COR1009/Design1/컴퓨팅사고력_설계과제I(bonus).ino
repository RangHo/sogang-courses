/*
  PPT의 requirements 대로 '초록->노랑->빨강' 을 시리얼 모니터에 넣음으로서 점등 인터벌을 조절할 수 있습니다.
  또한, 각 부분을 함수로 나누어서, 모듈화하였습니다.
  delay() 대신 millis() 를 이용하였습니다.
  아두이노 자체의 처리속도 때문에 정확하게 몇 ms의 오차는 존재할 수 있습니다.
*/

#include <Arduino.h>
#include <string.h>

//------------String Parsing 용 변수들----------------
String Inputstring; //시리얼로 읽은 스트링이 저장될 곳.

String delaystring1; //int로 변환 전 스트링들의 임시 저장용 스트링.
String delaystring2;
String delaystring3;

byte ind1; //delay 값 추출시 사용되는 인덱스. 용량을 조금이나마 줄이기 위해 byte로 정의함.
byte ind2;
byte ind3;
//--------------------------------------------------
int delay1 = 0; //딜레이 정의.
int delay2 = 0;
int delay3 = 0;

const byte red = 2; //LED 핀 정의. 용량을 조금이나마 줄이기 위해 byte 로 정의함.
const byte yellow = 3;
const byte green = 4;

unsigned long grnmillis = 0; //millis() 세팅을 위해 쓰일 변수
unsigned long yellowmillis = 0;
unsigned long redmillis = 0;
unsigned long current = 0;

//==================================================

void setup()
{
  Serial.begin(9600); //시리얼 셋업.

  pinMode(red, OUTPUT); //핀을 output으로 정의.
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  Serial.println("초록->노랑->빨강 순으로 제어 시간을 입력하세요.");
  Serial.println("입력한 숫자의 100배 간격으로 점멸됩니다.(단위: ms)");
}

//==================================================

void loop()
{
  GetIntervals();
  flash(delay1, delay2, delay3, green, yellow, red);
}

//==================================================
//주어진 딜레이 간격만큼 깜빡이는 함수. flash(딜레이1, 딜레이2, 딜레이3, led1, led2,led3); 으로 불러옵니다.

void flash(int delayval1, int delayval2, int delayval3, byte led1, byte led2, byte led3)
{

  digitalWrite(led3, 0);
  grnmillis = millis() + delayval1;
  digitalWrite(led1, 1);

  for (int i = (delayval1 / 100); i > 0; i--)
  { //delayval/100 회동안 반복.
    current = millis();
    while (millis() < current + 100)
    { //100ms 동안 "대기"
    }
    Serial.print(grnmillis - millis() + 100); //시리얼 출력
    Serial.println("ms until Yellow");
  }
  digitalWrite(led1, 0); //점등
  digitalWrite(led2, 1);
  //--------------------------------------------------
  yellowmillis = millis() + delayval2;

  for (int i = (delayval2 / 100); i > 0; i--)
  {
    current = millis();
    while (millis() < current + 100)
    {
    }
    Serial.print((yellowmillis + delayval3) - millis() + 100);
    Serial.println("ms until Green");
  }
  digitalWrite(led2, 0);
  digitalWrite(led3, 1);
  //--------------------------------------------------
  redmillis = millis() + delayval3;

  for (int i = (delayval3 / 100); i > 1; i--)
  {
    current = millis();
    while (millis() < current + 100)
    {
    }
    Serial.print(redmillis - millis() + 100);
    Serial.println("ms until Green");
  }

  if (delayval3 != 0)
  {
    current = millis();
    while (millis() < current + 90)
    { //그 10ms 를 보정하기 위해서 여기서 한번만 90ms만 "대기"합니다.
    }
    Serial.print(redmillis - millis() + 90);
    Serial.println("ms until Green");
    Serial.println("");
  }
}

//==================================================
//시리얼 통신을 통해서 딜레이를 받아오는 함수.

void GetIntervals()
{
  if (Serial.available())
  {
    current = millis();
    while (millis() < current + 10)
    {
    } //시리얼 통신의 처리를 위해 조금 기다려줍시다.

    while (Serial.available() != 0)
    {
      char c = Serial.read();
      Inputstring += c;
    }

    ind1 = Inputstring.indexOf('-');               //화살표(->) 의 '-' 를 찾음.
    delaystring1 = Inputstring.substring(0, ind1); //delaystring1 을 '-' 전까지의 문자로 정의.
    ind2 = Inputstring.indexOf('-', ind1 + 2);     //화살표를 건너뛴 뒤, 위의 과정을 반복.
    delaystring2 = Inputstring.substring(ind1 + 2, ind2);
    ind3 = Inputstring.indexOf('-', ind2 + 2);
    delaystring3 = Inputstring.substring(ind2 + 2);

    delay1 = delaystring1.toInt(); //delay 에 delaystring 을 int 형태로 변환하여 저장.
    delay2 = delaystring2.toInt();
    delay3 = delaystring3.toInt();

    delay1 *= 100; //100을 곱함.
    delay2 *= 100;
    delay3 *= 100;

    Serial.print("Green Delay = "); //출력.
    Serial.print(delay1);
    Serial.println("ms");
    Serial.print("Yellow Delay = ");
    Serial.print(delay2);
    Serial.println("ms");
    Serial.print("Red Delay = ");
    Serial.print(delay3);
    Serial.println("ms");
    Serial.println();

    Inputstring = ""; //추후 재입력되는 딜레이를 받기 위해서 스트링들을 비움.
    delaystring1 = "";
    delaystring2 = "";
    delaystring3 = "";
  }
}