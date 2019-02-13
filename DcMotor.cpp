//*** LIBRARIES ***

#include "DcMotor.h"
#include <arduino.h>
#include <AutoPID.h>


//*** CONSTRUCTOR ***

DcMotor::DcMotor(uint8_t motorID){

  this -> motorID = motorID; // Two motors availables : motor 1 and motor 2
  
  Encoder1 = new RotaryIncrementalEncoder(motorID);
  myPID = new AutoPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
  myPID->setTimeStep(2);
  Encoder1->StartSpeedMeasurement();
}


//*** FUNCTIONS ***

void DcMotor::setMotorSpeed(uint8_t motorSpeed){

  desiredMotorSpeed = 180;
  motorSpeedMeasure = Encoder1->GetSpeed(); 
  myPID->run();
  analogWrite(7, outputVal);
  

  Serial.print(desiredMotorSpeed);
  Serial.print(", ");
  Serial.print(motorSpeedMeasure);
  Serial.print(", ");
  Serial.print(outputVal);
  Serial.print(", ");
  Serial.print(desiredMotorSpeed - motorSpeedMeasure);
  Serial.println();
  
  //analogWrite(7, 150);
}
