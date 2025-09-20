#include <ESP32Servo.h>

Servo servos[6];
Servo escs[8];




int servoPins[] = {12, 13, 14, 15, 16, 17};
int escPins[] = {18, 19, 20, 21, 22, 23, 24, 25};


int inputServoX = 32, inputServoY = 33, inputServoRot = 34, inputDrone = 35;

int readX = 0, readY = 0, readRot = 0, readDrone = 0;
int posX = 90, posY = 90, rotationRate = 0, dronePwr = 1000;

int ADC_MAX = 4095;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  Serial.println("Servo start");
  for (int i = 0; i < 6; i++)
  {
    servos[i].setPeriodHertz(50);
    servos[i].attach(servoPins[i], 500, 2400);
    servos[i].write(90);
  }

  delay(1000);

  Serial.println("Test servos online");

  for (int j = 0; j < 8; j++)
  {
    escs[j].setPeriodHertz(50);
    escs[j].attach(escPins[j], 1000, 2000);
    escs[j].writeMicroseconds(1000);
  }
  
  delay(5000);
  Serial.println("ESC motors online");

}

void loop() {
  
  readX = analogRead(inputServoX);
  readY = analogRead(inputServoY);
  readRot = analogRead(inputServoRot);

  readDrone = analogRead(inputDrone);

  posX = map(readX, 0, ADC_MAX, 0, 180);
  posY = map(readY, 0, ADC_MAX, 0, 180);
  dronePwr = map(readDrone, 0, ADC_MAX, 1000, 2000);

  delay(50);
  for (int k = 0; k < 6; k++)
  {
    servos[k].write(pos);
  }
  delay(20);

  if (pos > 82 && pos < 97)
  {
    for (int i = 0; i < 8; i++)
    {
      escs[i].writeMicroseconds(1800);
    }
    
  }
  else
  {
    for (int j = 0; j < 8; j++)
    {
      escs[j].writeMicroseconds(1000);
    }
  }

  delay(20);

}