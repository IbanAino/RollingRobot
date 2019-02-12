#include "RotaryIncrementalEncoder.h"
#include <arduino.h>


// CONSTRUCTOR
RotaryIncrementalEncoder::RotaryIncrementalEncoder(uint8_t encoderID){

  this -> encoderID = encoderID; // two encoders availables : encoder 1 and encoder 2

  flagMeasureRotation = false;

  // Encoder 1 sensors A and B
  hardwarePinEncoderSensorA = 2;
  hardwarePinEncoderSensorB = 3;
  //Encoder 2 sensors C and D
  hardwarePinEncoderSensorC = 18;
  hardwarePinEncoderSensorD = 19;

  pinMode(hardwarePinEncoderSensorA, INPUT_PULLUP);
  pinMode(hardwarePinEncoderSensorB, INPUT_PULLUP);
  pinMode(hardwarePinEncoderSensorC, INPUT_PULLUP);
  pinMode(hardwarePinEncoderSensorD, INPUT_PULLUP);

  switch(encoderID){
    case 1 :
      attachInterrupt(digitalPinToInterrupt(hardwarePinEncoderSensorA), handleInterruptA, CHANGE); // Encoder 1
    break;
    case 2 :
      attachInterrupt(digitalPinToInterrupt(hardwarePinEncoderSensorC), handleInterruptC, CHANGE); // Encoder 2
    break;
  }
}


// FUNCTIONS
void RotaryIncrementalEncoder::StartSpeedMeasurement(){
  flagMeasureSpeed = true;
  
  // Reset couteres and timer
  encoderSpeedRightCounter = 0;
  encoderSpeedLeftCounter = 0;
  timeMilllisecond = millis();
}

void RotaryIncrementalEncoder::StopSpeedMeasurement(){
  flagMeasureSpeed = false;
}

int16_t RotaryIncrementalEncoder::GetSpeed(){
  
  if(encoderID == 1){
    int16_t motorSpeed = (encoderSpeedRightCounter * 100)/(millis() - timeMilllisecond);
    timeMilllisecond = millis();
    encoderSpeedRightCounter = 0;
    return(motorSpeed);
  }
  else if(encoderID == 2){
    int16_t motorSpeed = (encoderSpeedLeftCounter * 100)/(millis() - timeMilllisecond);
    timeMilllisecond = millis();
    encoderSpeedLeftCounter = 0;
    return(motorSpeed);
  } 
}

void RotaryIncrementalEncoder::StartRotationMeasurement(){
  flagMeasureRotation = true;
}

void RotaryIncrementalEncoder::StopRotationMeasurement(){
  flagMeasureRotation = false;
}

int16_t RotaryIncrementalEncoder::GetRotation(){
  switch(encoderID){
    case 1 :
      return(encoderRotationRightCounter);
    break;
    case 2 :
      return(encoderRotationLeftCounter);
    break;
  }
}

// Encoder 1
static void RotaryIncrementalEncoder::handleInterruptA(){
  // Speed measurement
  if(flagMeasureSpeed){
    encoderSpeedRightCounter++;
  }
  
  // Rotation measurement
  if(flagMeasureRotation){
    if (digitalRead(2) == HIGH) {
      if (digitalRead(3) == LOW) {
        encoderRotationRightCounter++;
      } else {
        encoderRotationRightCounter--;
      }
    } else {
      if (digitalRead(3) == LOW) {
        encoderRotationRightCounter--;
      } else {
        encoderRotationRightCounter++;
      }
    }
  }
}

// Encoder 2
void RotaryIncrementalEncoder::handleInterruptC(){
  // Speed measurement
  if(flagMeasureSpeed){
    encoderSpeedLeftCounter++;
  }
  
  // Rotation measurement
  if(flagMeasureRotation){
    if (digitalRead(18) == HIGH) {
      if (digitalRead(19) == LOW) {
        encoderRotationLeftCounter++;
      } else {
        encoderRotationLeftCounter--;
      }
    } else {
      if (digitalRead(19) == LOW) {
        encoderRotationLeftCounter--;
      } else {
        encoderRotationLeftCounter++;
      }
    }
  }
}
