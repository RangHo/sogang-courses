#include <Arduino.h>

#include <Servo.h> // 서보 모터 라이브러리를 프로그램에 추가
const int SERVO = 9; // 서보 모터를 제어할 핀 번호
const int rowPins[4] = {18, 19, 20, 21};
const int colPins[4] = {17, 16, 15, 14}; // key matrix 핀 번호
const int degreeMap[4][4] = {
  {20, 40, 60, -1},
  {80, 100, 120, -1},
  {140, 160, 180, -1},
  {-1, 0, -1, -1},  
}; // 0~9에 해당하는 각도 저장 (0 : 0도, 2 : 40도, ... , 9 : 180도)
long  input_delay  = 0;
Servo myServo; // 객체 생성. 연결된 서보 모터에 내릴 명령을 myServo 객체를 참고하여 입력

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO); // 서보 모터 초기화
  for(int index=0; index<4; index++) { // 인풋, 아웃풋 핀 모드 설정
    pinMode(rowPins[index], INPUT_PULLUP); // 내부적으로 풀업 저항 사용
    pinMode(colPins[index], OUTPUT);
    digitalWrite(colPins[index], HIGH); // column을 high로 초기화
  }
}

void loop() {
  int degree = -1;
  for(int column=0; column<4; column++) { // key matrix의 column을 순차적으로 LOW로 만듬
    digitalWrite(colPins[column], LOW); // column을 하나씩 LOW로 출력
    for(int row=0; row<4; row++) {
      if(digitalRead(rowPins[row]) == LOW) { // 4 개 row의 입력값을 순차적으로 확인
        if(millis() -  input_delay  > 200) { //  input_delay  200 ms
           input_delay  = millis();
          degree = degreeMap[row][column]; // LOW가 입력되었을 때의 row, column을 이용하여 degreeMap 배열에서 각 버튼에 대응하는 값을 읽음
        }
      }
    }
    digitalWrite(colPins[column], HIGH);
  }
  if(degree >= 0) {
    myServo.write(degree);
    Serial.print("degree : ");
    Serial.println(degree);
  }
}
