#include <Arduino.h>

int f = 0;
float c = 0;
bool con = 1;
//--------------

void setup() {
Serial.begin(9600);
}

float f_to_c(int temp_F){

  float temp_C = 5.0/9.0*(temp_F-32.0);
  return temp_C;

}


void loop() {
while(con){
for(f=0;f<=100;f+=10){
  c= f_to_c(f);
  Serial.print(f); Serial.print(" F = ");
  Serial.print(c); Serial.println(" C");
  }

    con = 0;
    }
}

