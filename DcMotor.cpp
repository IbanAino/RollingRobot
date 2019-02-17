//*** LIBRARIES ***

#include "DcMotor.h"
#include <arduino.h>
#include <AutoPID.h>



//*** CONSTRUCTOR ***

DcMotor::DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2){

  this -> motorID = motorID; // Two motors availables : motor 1 and motor 2
  this -> hardwarePinHStructureIN1 = hardwarePinHStructureIN1;
  this -> hardwarePinHStructureIN2 = hardwarePinHStructureIN2;

  // Set motor sense to stop
  pinMode(hardwarePinHStructureIN1, OUTPUT);
  pinMode(hardwarePinHStructureIN2, OUTPUT);
  digitalWrite(hardwarePinHStructureIN1, LOW);
  digitalWrite(hardwarePinHStructureIN2, LOW);
  
  Encoder1 = new RotaryIncrementalEncoder(motorID);
  myPID = new AutoPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
  myPID->setTimeStep(2);
  myPID->setBangBang(100);
  Encoder1->StartSpeedMeasurement();
}


//*** FUNCTIONS ***

void DcMotor::setMotorSense(bool sense){
  if(sense){
    digitalWrite(hardwarePinHStructureIN1, HIGH);
    digitalWrite(hardwarePinHStructureIN2, LOW);
  }else{
    digitalWrite(hardwarePinHStructureIN1, LOW);
    digitalWrite(hardwarePinHStructureIN2, HIGH);
  }
}

void DcMotor::setMotorSpeed(uint8_t motorSpeed){

  desiredMotorSpeed = motorSpeed;
  motorSpeedMeasure = Encoder1->GetSpeed(); 
  myPID->run();
  analogWrite(hardwarePinoutSpeed, outputVal);

  Serial.print(desiredMotorSpeed);
  Serial.print(", ");
  Serial.print(motorSpeedMeasure);
  Serial.print(", ");
  Serial.print(outputVal);
  Serial.print(", ");
  Serial.print(desiredMotorSpeed - motorSpeedMeasure);
  Serial.println();
}
