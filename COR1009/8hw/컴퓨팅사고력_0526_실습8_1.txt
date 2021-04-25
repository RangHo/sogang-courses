const int pin[8] = {36, 37, 38, 39, 40, 41, 42, 43}; 
const int com[4] = {28, 29, 30, 31};


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
}; // 숫자 ‘0 ~ 9‘에 해당하는 세그먼트 입력

void setup() {
  for(int i=0; i<8; i++)
  {
    pinMode(pin[i], OUTPUT); // pin 36~43를 출력으로 설정
  }
  for(int i=0; i<4; i++)
  {
    pinMode(com[i], OUTPUT); // pin 28~31을 출력으로 설정
  }
}

void loop() {
  for(int i=0; i<4; i++) // 7 세그먼트 어레이의 각 디스플레이를 순차적으로 설정
  {
    for(int j=0; j<4; j++) 
    {digitalWrite(com[j], HIGH); } // 7 세그먼트 어레이를 모두 끔

    switch(i) {
      case 0: // 7 세그먼트 어레이의 첫번째 디스플레이 출력을 설정
        for(int num=0; num<8; num++){
          digitalWrite(pin[num], digits[1][num]);}
        break;
      case 1: // 7 세그먼트 어레이의 두번째 디스플레이 출력을 설정
        for(int num=0; num<8; num++){
          digitalWrite(pin[num], digits[2][num]);}
        break;
      case 2: // 7 세그먼트 어레이의 세번째 디스플레이 출력을 설정
       for(int num=0; num<8; num++){
          digitalWrite(pin[num], digits[3][num]);}
        break;
      case 3: // 7 세그먼트 어레이의 네번째 디스플레이 출력을 설정
        for(int num=0; num<8; num++){
          digitalWrite(pin[num], digits[4][num]); }
        break;
      default:
        break;
    }
    digitalWrite(com[i], LOW);
  }
}
