#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 5
#define SS_PIN 53
#define SERVO 9
MFRC522 mfrc522(SS_PIN, RST_PIN);           // mfrc522 객체생성
Servo myservo;                              // myservo 객체생성
byte IDbuffer[] = {0x00, 0x00, 0x00, 0x00}; // ID 저장을 위한 배열

void setup()
{
  Serial.begin(9600);
  SPI.begin();           // SPI 시작
  mfrc522.PCD_Init();    //RFID 모듈 시작
  myservo.attach(SERVO); // 9번 핀을 서보제어에 사용
  Serial.println("Scan a card and store cardID.");
  while (!mfrc522.PICC_IsNewCardPresent())
    ; // RFID 카드가 접촉될 때까지 대기
  while (!mfrc522.PICC_ReadCardSerial())
    ;                                             // RFID의 ID를 읽을 때까지 대기
  storeID(mfrc522.uid.uidByte, mfrc522.uid.size); // 읽어들인 ID (~.uidByte) 크기(4자리수, ~uid.size)를 저장
  mfrc522.PICC_HaltA();                           // RFID 동작 정지
  myservo.write(0);                               // 서보 모터 위치 초기화
}
void loop()
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return; // 접촉된 RFID 카드가 없는 경우 loop 함수 종료하고,  loop 다시 시작
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
    // 접촉된 RFID 카드의 ID를 읽을 수 없는 경우 loop 함수 종료하고 loop 다시 시작
  }
  compareID(mfrc522.uid.uidByte, mfrc522.uid.size);
  // 초기에 저장한 RFID 카드와 새로 읽은 카드의 ID를 비교
  mfrc522.PICC_HaltA(); // RFID 정지
}
void compareID(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  { // 저장된 ID와 새로 읽은 ID 배열을 비교
    if (buffer[i] == IDbuffer[i])
    { // 같으면 비교 계속, 다르면 비교 중지
      continue;
    }
    else
    {
      Serial.println("WRONG ID");
      tone(2, 392, 1000);
      return;
    }
  }
  Serial.println("CORRECT ID"); // 마지막까지 ID가 같은 경우 서보모터 동작
  myservo.write(90);            // 도어락 열림
  delay(2000);                  //2초후 다시 닫음
  myservo.write(0);
}

void storeID(byte *buffer, byte bufferSize)
{
  Serial.print("stored ID : ");
  for (int i = 0; i < bufferSize; i++)
  {
    IDbuffer[i] = buffer[i]; // 새로 읽은 ID 배열을 저장
    if (buffer[i] < 0x10)
    {
      Serial.print(" 0");
    }
    else
    {
      Serial.print(" ");
    }
    //한자리 16진수이면 한칸 띄고 0을 앞에 붙여서 프린트, 두자리이면 한칸만 띄고 프린트
    Serial.print(buffer[i], HEX); // 읽어들인 ID를 16진수 형태로 표시
  }
  Serial.println();
}
