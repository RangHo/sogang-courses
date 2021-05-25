/*
 하나로 여러가지 가전제품을 조종할 수 있는 다용도/유니버셜 리모컨입니다.
 버튼 매트릭스로 가전제품을 조종하고, 가변저항으로 조종할 가전제품을 선택합니다.
 제공받은 키트에 IR 송신 모둘이 없어서 IR 근접센서를 이용해서 리모컨 신호를 송신하였습니다.
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

IRsend irsend; //IR 클래스 생성

//-----------------핀 정의--------------------------
const int pot = A0;                //가변저항
const int SW = 3;                  //선택스위치
const int ModeLED = 13;            //상태표시용 LED
byte rowPins[4] = {12, 11, 10, 8}; //키패드
byte colPins[4] = {7, 6, 5, 4};

//-----------모드 설정에 사용되는것들-------------
bool Switchingmode = 0; //리모컨 기능 사용 여부
int analogvalue = 0;    //가변저항 값이 저장됨
int prevPos = 0;        //이전 모드
int Position = 0;       // 현재 모드

//--------------LCD 에 사용되는것들-------------------
LiquidCrystal_I2C lcd(0x3F, 16, 2); //LCD 지정. I2C 주소가 다르면 이거 바꿔야해요

//---------------키패드에 사용되는것들-----------------
long input_delay = 0;
const int KeyArray[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
};
int currentkey = 0;

//---------------그 외 기타 변수들-------------------
unsigned long LastTimermillis = 0; //LCD 백라이트를 위한 변수.

//--------------------------------------------------
int GetKeypad();
void SendSignal(int mode, int button);
//==================================================
void setup()
{
  Serial.begin(9600); //시리얼은 디버깅 및 트터블슈팅용입니다.

  lcd.init();
  lcd.backlight();

  for (int index = 0; index < 4; index++)
  {
    pinMode(rowPins[index], INPUT_PULLUP);
    pinMode(colPins[index], OUTPUT);
    digitalWrite(colPins[index], HIGH);
  }

  pinMode(SW, INPUT);
  pinMode(ModeLED, OUTPUT);
}
//==================================================
void loop()
{

  if ((digitalRead(SW)) == HIGH)
  {                                   //모드 선택 <--> 리모컨 기능 토글.
    while ((digitalRead(SW)) == HIGH) // 눌렀을때 무한반복하지 않도록 눌렀다 뗄때까지 대기. 디바운싱 효과도 있음.
    {
      delay(10);
    }

    if (Switchingmode == 0)
    { //모드 선택
      Switchingmode = 1;
      // Serial.println("Select Remote");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Select Function"); //LCD 에 표시.
      digitalWrite(ModeLED, 1);     //불 켜요
    }
    else if (Switchingmode == 1)
    { //리모컨 기능 사용
      Switchingmode = 0;
      // Serial.println("Control Mode");
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Control Mode"); //LCD 에 표시.
      digitalWrite(ModeLED, 0);  //불 꺼요
    }

    LastTimermillis = millis(); //LCD 백라이트 타이머 리셋.
    lcd.backlight();
  }

  if (Switchingmode == 1)
  { //가변저항의 값을 읽고 그에 따라서 조종할 제품을 바꿔줍니다.
    analogvalue = analogRead(pot);
    if (analogvalue < 300)
    {
      Position = 0;
    }
    else if (analogvalue > 300 && analogvalue < 500)
    {
      Position = 1;
    }
    else if (analogvalue > 500 && analogvalue < 700)
    {
      Position = 2;
    }
    else if (analogvalue > 700 && analogvalue < 900)
    {
      Position = 3;
    }
    else if (analogvalue > 900)
    {
      Position = 4;
    }
    //Serial.println(analogvalue);

    lcd.setCursor(0, 1);

    switch (Position)
    {
    case 0:
      lcd.print("TV");
      break;
    case 1:
      lcd.print("STB");
      break;
    case 2:
      lcd.print("A/C");
      break;
    case 3:
      lcd.print("Custom_1");
      break;
    case 4:
      lcd.print("Generic_NEC");
      break;
    default:
      break;
    }

    if (prevPos != Position)
    {
      LastTimermillis = millis(); //LCD 백라이트 타이머 리셋.
      lcd.backlight();
      lcd.setCursor(0, 1);
      lcd.print("                "); //LCD 2째줄을 공백문자로 채움으로써 '리셋'.
    }

    prevPos = Position;
  }

  if (Switchingmode == 0)
  {                           //키패드 신호를 받아서 이를 바탕으로 IR 신호 송신.
    currentkey = GetKeypad(); //키패드 받아옴
    if (currentkey != 0)
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Control Mode");
      lcd.setCursor(2, 1);
      lcd.print(currentkey);
      //Serial.println(currentkey);

      SendSignal(Position, currentkey); //IR LED호 신호를 보냄.
    }
  }

  if ((millis() - LastTimermillis) > 5000)
  { //5초 이상 입력이 없으면 LCD의 백라이트를 끔.
    lcd.noBacklight();
  }
}
//==================================================
int GetKeypad()
{ //버튼 매트릭스에서 어떤 버튼을 눌렀는지 받아오는 함수.
  int Output = 0;
  int KeyInput = 0;
  for (int column = 0; column < 4; column++)
  {
    digitalWrite(colPins[column], LOW);
    for (int row = 0; row < 4; row++)
    {
      if (digitalRead(rowPins[row]) == LOW)
      {
        if (millis() - input_delay > 200)
        {
          input_delay = millis();
          KeyInput = KeyArray[row][column];
        }
      }
    }
    digitalWrite(colPins[column], HIGH);
  }
  if (KeyInput > 0)
  {
    Output = KeyInput;
    KeyInput = 0;
    LastTimermillis = millis(); //LCD 백라이트 타이머 리셋
    lcd.backlight();
    // Serial.println("KeyPressed");
    return (Output); //누른 버튼이 몇번인지를 리턴
  }
  else
  {
    return 0; // 버튼이 안 눌렸을시 return 0;
  }
}
//==================================================
void SendSignal(int mode, int button)
{ //두 변수(int mode, int button) 을 바탕으로 IR 신호를 송신하는 함수. 지정 안한거는 임시로 전원버튼으로 세팅함.

  if (mode == 0)
  { //TV
    switch (button)
    {
    case 16:
      irsend.sendNEC(0x20DF10EF, 32); //전원
      break;

    case 15:
      irsend.sendNEC(0x20DFD02F, 32); //외부입력
      break;

    case 14:
      irsend.sendNEC(0x20DF40BF, 32); //음량 높임
      break;

    case 13:
      irsend.sendNEC(0x20DF00FF, 32); //채널 위로
      break;

    case 12:
      irsend.sendNEC(0x20DFE01F, 32);
      break;

    case 11:
      irsend.sendNEC(0x20DF02FD, 32); //위
      break;

    case 10:
      irsend.sendNEC(0x20DFC03F, 32); //음량 낮춤
      break;

    case 9:
      irsend.sendNEC(0x20DF807F, 32); //채널 아래로
      break;

    case 8:
      irsend.sendNEC(0x20DFE01F, 32); //왼쪽
      break;

    case 7:
      irsend.sendNEC(0x20DF22DD, 32); //ok
      break;

    case 6:
      irsend.sendNEC(0x20DF609F, 32); //오른쪽
      break;

    case 5:
      irsend.sendNEC(0x20DF7887, 32); // 홈? 리모컨 '가운데'에 있는 버튼 1
      break;

    case 4:
      irsend.sendNEC(0x20DFD02F, 32);
      break;

    case 3:
      irsend.sendNEC(0x20DF827D, 32); //아래
      break;

    case 2:
      irsend.sendNEC(0x20DFD02F, 32);
      break;

    case 1:
      irsend.sendNEC(0x20DF906F, 32); //리모컨 '가운데' 버튼 2
      break;

    default:
      break;
    }
  }
  else if (mode == 1)
  { //셋탑박스
    switch (button)
    {
    case 16:
      irsend.sendNEC(0x1FE807F, 32); //전원
      break;
    case 15:
      irsend.sendNEC(0x20DF50AF, 32); //외부입력
      break;
    case 14:
      irsend.sendNEC(0x1FEC23D, 32); //음량 높임
      break;
    case 13:
      irsend.sendNEC(0x1FE02FD, 32); //채널 위
      break;
    case 12:
      irsend.sendNEC(0x1FE807F, 32);
      break;
    case 11:
      irsend.sendNEC(0x1FE926D, 32); //위
      break;
    case 10:
      irsend.sendNEC(0x1FE42BD, 32); //음량 낮춤
      break;
    case 9:
      irsend.sendNEC(0x1FE827D, 32); //채널 아래
      break;
    case 8:
      irsend.sendNEC(0x1FED22D, 32); //왼쪽
      break;
    case 7:
      irsend.sendNEC(0x1FE629D, 32); //ok
      break;
    case 6:
      irsend.sendNEC(0x1FE32CD, 32); //오른쪽
      break;
    case 5:
      irsend.sendNEC(0x1FE40BF, 32); //'가운데' 1
      break;
    case 4:
      irsend.sendNEC(0x1FE807F, 32);
      break;
    case 3:
      irsend.sendNEC(0x1FE52AD, 32); //아래
      break;
    case 2:
      irsend.sendNEC(0x1FE807F, 32);
      break;
    case 1:
      irsend.sendNEC(0x1FEB24D, 32); //'가운데' 2
      break;

    default:
      break;
    }
  }
  else if (mode == 2)
  { //AC
    switch (button)
    {
    case 16:
      irsend.sendLG(0x880064A, 28);
      break;
    case 15:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 14:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 13:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 12:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 11:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 10:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 9:
      irsend.sendLG(0x88C0051, 28);
      break;
    case 8:
      irsend.sendLG(0x8808A46, 28);
      break;
    case 7:
      irsend.sendLG(0x8808945, 28);
      break;
    case 6:
      irsend.sendLG(0x8808844, 28);
      break;
    case 5:
      irsend.sendLG(0x8808743, 28);
      break;
    case 4:
      irsend.sendLG(0x8808642, 28);
      break;
    case 3:
      irsend.sendLG(0x8808541, 28);
      break;
    case 2:
      irsend.sendLG(0x8808440, 28);
      break;
    case 1:
      irsend.sendLG(0x880834F, 28);
      break;

    default:
      break;
    }
  }
  else if (mode == 3)
  { //Custom 1
    switch (button)
    {
    case 16:
      irsend.sendNEC(0x0177013, 32); // 임시 커스텀 코드 1
      break;

    default:
      break;
    }
  }
  else if (mode == 4)
  { //Generic NEC Remote
    switch (button)
    {
    case 16:
      irsend.sendNEC(0xFFA25D, 32); //CH-
      break;
    case 15:
      irsend.sendNEC(0xFF629D, 32); //CH
      break;
    case 14:
      irsend.sendNEC(0xFFE21D, 32); //CH+
      break;
    case 13:
      irsend.sendNEC(0xFF22DD, 32); // |<<
      break;
    case 12:
      irsend.sendNEC(0xFF02FD, 32); // >>|
      break;
    case 11:
      irsend.sendNEC(0xFFC23D, 32); // >||
      break;
    case 10:
      irsend.sendNEC(0xFFE01F, 32); // -
      break;
    case 9:
      irsend.sendNEC(0xFFA857, 32); // +
      break;
    case 8:
      irsend.sendNEC(0xFF906F, 32); //EQ
      break;
    case 7:
      irsend.sendNEC(0xFF9867, 32); //0
      break;
    case 6:
      irsend.sendNEC(0xFFB04F, 32); //100+
      break;
    case 5:
      irsend.sendNEC(0xFF30CF, 32); //200+
      break;
    case 4:
      irsend.sendNEC(0xFF18E7, 32); //1
      break;
    case 3:
      irsend.sendNEC(0xFF7A85, 32); //2
      break;
    case 2:
      irsend.sendNEC(0xFF10EF, 32); //3
      break;
    case 1:
      irsend.sendNEC(0xFF38C7, 32); //4
      break;

    default:
      break;
    }
  }
}