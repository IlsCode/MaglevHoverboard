#include <Servo.h>

Servo servo1;
Servo esc1, esc2;

int servo1Pin = 9;
int esc1Pin = 10;
int esc2Pin = 11;

int readingValue = 0;
int readingPin = A1;
int pos = 0;
int ADC_MAX = 1023;

void setup() {
  Serial.begin(115200);
  Serial.println("Arduino test");

  servo1.attach(servo1Pin);
  esc1.attach(esc1Pin);
  esc2.attach(esc2Pin);

  Serial.println("Beginning motor test");


}

void loop() {

  readingValue = analogRead(readingPin);
  pos = map(readingValue, 0, ADC_MAX, 0, 180);
  delay(100);
  servo1.write(pos);
  if (pos >= 85 && pos <= 95)
  {
    esc1.writeMicroseconds(2000);
    esc2.writeMicroseconds(2000);
    
  }
  else if (pos <= 84 || pos >= 96)
  {
    esc1.writeMicroseconds(1000);
    esc2.writeMicroseconds(1000);
  }


}
