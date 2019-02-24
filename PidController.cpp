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
  integralError = 0;
  previousError = 0;
}

//*** FUNCTIONS ***
float PidController::SetSetPoint(float setPoint){
  this -> setPoint = setPoint;
}

float PidController::Compute(float measurement){
  float error = setPoint - measurement;

  integralError += error;

  float derivativeError = (error - previousError);
  previousError = error;

  outputVal += (error * kP + integralError * kI + derivativeError * kD);

  if(outputVal > outputMax){
    outputVal = outputMax;
  }else if(outputVal < outputMin){
    outputVal = outputMin;
  }
  
  return(outputVal);
}
