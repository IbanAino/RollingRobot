//*** LIBRARIES ***
#include <arduino.h>
#include "PidController.h"

//*** CONSTRUCTOR ***
PidController::PidController(float kP, float kI, float kD, float outputMin, float outputMax){
  this -> kP = kP;
  this -> kI = kI;
  this -> kD = kD;
  this -> outputMin = outputMin;
  this -> outputMax = outputMax;

  outputVal = 0;
}

//*** FUNCTIONS ***
float PidController::setSetPoint(float setPoint){
  this -> setPoint = setPoint;
}

float PidController::compute(float measurement){
  float error = setPoint - measurement;

  outputVal = outputVal * kP;
  
  return(outputVal);
}
