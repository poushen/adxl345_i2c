#include "adxl345.h"

adxl345 ad;
int readings[3] = {0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start : \n");
    
  ad.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(50);

  //13-bit, sign extended values.
  ad.getOutput(readings);

  // mg value
  int x,y,z;
  float rate = 32000.0 / 8192.0;    // 2^13 = 8192, +-16g => 32g => 32000mg
  x = readings[0] * rate;
  y = readings[1] * rate;
  z = readings[2] * rate;
  
  Serial.print("X= ");
  Serial.print(x);
  Serial.print("    Y= ");
  Serial.print(y);
  Serial.print("    Z= ");
  Serial.println(z);
}

