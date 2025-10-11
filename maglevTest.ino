#include <ESP32Servo.h>

Servo servos[6];
Servo escs[8];


int servoPins[] = {12, 13, 14, 15, 16, 17};
int escPins[] = {18, 20, 22, 23, 25, 24, 27, 32};


int inputServoX = 2, inputServoY = 3, inputDrone = 4, inputServoRot = 5;

int readX = 0, readY = 0, readRot = 0, readDrone = 0;
int posX = 90, posY = 90, rotationRate = 90, dronePwr = 1000;

int ADC_MAX = 4095;

int angleTune = 30;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  pinMode(inputServoX, INPUT);
  pinMode(inputServoY, INPUT);
  pinMode(inputServoRot, INPUT);

  Serial.println("Servo start");
  for (int i = 0; i < 6; i++)
  {
    servos[i].setPeriodHertz(50);
    servos[i].attach(servoPins[i], 500, 2400);
    servos[i].write(130);
  }

  delay(1000);

  Serial.println("Servos online");

  for (int j = 0; j < 8; j++)
  {
    escs[j].setPeriodHertz(50);
    escs[j].attach(escPins[j], 1000, 2000);
    escs[j].writeMicroseconds(dronePwr);
    Serial.println("Attached ESC on");
    Serial.println(escPins[j]);
  }
  
  delay(10000);
  Serial.println("ESC motors online");

}

void loop() {
  
  readX = analogRead(inputServoX);
  readY = analogRead(inputServoY);
  readRot = analogRead(inputServoRot);


  readDrone = analogRead(inputDrone);
  
  // Review angle offsets, whether positive or negative
  posX = map(readX, 0, ADC_MAX, 0, 90);
  posY = map(readY, 0, ADC_MAX, 0, 90);
  dronePwr = map(readDrone, 0, ADC_MAX, 1000, 1500);


  rotationRate = map(readRot, 0, ADC_MAX, 0, 90);
  delay(10);

  
  if ((rotationRate+90) > 120)
  {
    // Assign corresponding servo reaction control to spin clockwise
    // Double check which servos is what pin, check the angles as well as negatives and positives
    servos[0].write(posY-40); // Bottom right Y about 60
    servos[1].write(posY+20); // Bottom Left Y about 120
    servos[2].write(posY-40); // Top Right Y about 60
    servos[3].write(posY+20); // Top Left Y about 120

    servos[4].write(posX-10); // Right X about 100
    servos[5].write(posX-10); // Left X about 100
  }
  
  if ((rotationRate+55) < 80)
  {
    servos[0].write(180-(posY+40)); // Bottom right Y about 60
    servos[1].write(180-(posY-20)); // Bottom Left Y about 120
    servos[2].write(180-(posY+40)); // Top Right Y about 60
    servos[3].write(180-(posY-20)); // Top Left Y about 120

    servos[4].write(posX-10); // Right X about 100
    servos[5].write(posX-10); // Left X about 100
  }


  if (abs(posY-110) <= 10 && abs(posX-110) <= 10)
  {
    servos[0].write(70); // Bottom right Y about 60
    servos[1].write(110); // Bottom Left Y about 120
    servos[2].write(65); // Top Right Y about 60
    servos[3].write(120); // Top Left Y about 120

    servos[4].write(100); // Right X about 100
    servos[5].write(100); // Left X about 100
  }
  else
  {
    servos[0].write(180-(posY)); // Bottom right Y about 60
    servos[1].write(posY); // Bottom Left Y about 120
    servos[2].write(180-(posY+5)); // Top Right Y about 60
    servos[3].write(posY+15); // Top Left Y about 120

    servos[4].write(posX-10); // Right X about 100
    servos[5].write(posX-10); // Left X about 100
  }
  

  for (int i = 0; i < 8; i++)
  {
    escs[i].writeMicroseconds(dronePwr);
  }

  delay(20);

}