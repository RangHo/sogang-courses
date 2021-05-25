#include <Arduino.h>

#include <LiquidCrystal_I2C.h> // LCD I2C 라이브러리 추가
#include <Wire.h>              // I2C 통신 라이브러리 추가
#include <Servo.h>
const int colPins[4] = {31, 29, 27, 25};
const int rowPins[4] = {33, 35, 37, 39}; // 키패드 제어핀 설정
const int keymap[4][4] = {
    {1, 2, 3, -1},
    {4, 5, 6, -1},
    {7, 8, 9, -1},
    {-1, 0, -1, -1}}; // 키패드 맵 설정

int errortimes = 0;
const int SERVO = 9;                // 서보 모터 제어핀 설정
LiquidCrystal_I2C lcd(0x3f, 16, 2); // 객체 선언
Servo myServo;                      // 객체 선언
const int password = 1234;          // 비밀번호 설정
long lastDebounce = 0;              //
int i = 0;                          //입력된 숫자 갯수
int pressedNumbers = 0;             // 입력된 번호
int numbers[4] = {0, 0, 0, 0};      // 키패드의 입력 값을 저장할 배열 선언

void setup()
{
  Serial.begin(9600);
  for (int index = 0; index < 4; index++)
  { // 인풋, 아웃풋 핀 모드 설정
    pinMode(rowPins[index], INPUT_PULLUP);
    // 내부적으로 풀업 저항 사용
    pinMode(colPins[index], OUTPUT);
    digitalWrite(colPins[index], HIGH); // column을 high로 초기화
  }
  lcd.init();            // LCD 스크린 초기화 (LCD 사용 시작)
  lcd.backlight();       // backlight 켜기
  myServo.attach(SERVO); // 서보 모터 초기화
}
void loop()
{
  lcd.setCursor(4, 0);
  lcd.print("Password");
  myServo.write(180); // 잠금 상태
  char key = -1;

  for (int column = 0; column < 4; column++)
  {
    digitalWrite(colPins[column], LOW);
    for (int row = 0; row < 4; row++)
    {
      if (digitalRead(rowPins[row]) == LOW)
      {
        if (millis() - lastDebounce > 200)
        {
          lastDebounce = millis();
          key = keymap[row][column];
        }
      }
    }
    digitalWrite(colPins[column], HIGH);
  }
  if (key != -1)
  {
    lcd.setCursor(5 + i, 1);
    lcd.print("*");
    delay(300);
    numbers[i] = key;
    pressedNumbers = 1000 * numbers[0] + 100 * numbers[1] + 10 * numbers[2] + numbers[3];
    // 입력된 값을 수로 변환
    Serial.println(numbers[i]);
    i++;
    if (i == 4)
    {
      if (pressedNumbers == password)
      { // password와 비교하여 값이 같을 때
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Correct");
        myServo.write(0); // 열린 상태
        errortimes = 0;
        delay(2000);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Wrong");
        delay(1000);
        errortimes++;
      }
      i = 0;
    }
  }

  if (errortimes > 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Three Times!");
    lcd.setCursor(0, 1);
    lcd.print("Try after 10sec");
    delay(10000);
    lcd.clear();
    errortimes = 0;
  }
}
