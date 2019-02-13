//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"
#include "DcMotor.h"


//*** VARIABLES ***

//PID settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 10
#define KI 3
#define KD 1
double motorSpeedMeasure, desiredMotorSpeed, outputVal;


//*** OBJECTS ***

DcMotor* motor1;


//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

  motor1 = new DcMotor(1);
}


//*** MAIN LOOP ***

void loop() {
  motor1 -> setMotorSpeed(120);
}
