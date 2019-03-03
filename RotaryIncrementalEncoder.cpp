#include "RotaryIncrementalEncoder.h"
#include <arduino.h>

// Static variables declarations
uint16_t RotaryIncrementalEncoder::encoder1_SpeedCounter;
uint16_t RotaryIncrementalEncoder::encoder2_SpeedCounter;
int16_t RotaryIncrementalEncoder::Encoder1_RotationCounter;
int16_t RotaryIncrementalEncoder::encoder2_RotationCounter;
bool RotaryIncrementalEncoder::flagMeasureSpeed;
bool RotaryIncrementalEncoder::flagMeasureRotation;


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
      attachInterrupt(digitalPinToInterrupt(hardwarePinEncoderSensorA), handleInterruptA, RISING); // Encoder 1
    break;
    case 2 :
      attachInterrupt(digitalPinToInterrupt(hardwarePinEncoderSensorC), handleInterruptC, RISING); // Encoder 2
    break;
  }
}


// FUNCTIONS

void RotaryIncrementalEncoder::StartSpeedMeasurement(){
  flagMeasureSpeed = true;
  
  // Reset couteres and timer
  encoder1_SpeedCounter = 0;
  encoder2_SpeedCounter = 0;
  timeMilllisecond = millis();
}

void RotaryIncrementalEncoder::StopSpeedMeasurement(){
  flagMeasureSpeed = false;
}

float RotaryIncrementalEncoder::GetSpeed(){ // retrune motor speed in rotations/seconds
  
  if(encoderID == 1){
    float motorSpeed = (encoder1_SpeedCounter * 1000)/(millis() - timeMilllisecond);
    timeMilllisecond = millis();
    encoder1_SpeedCounter = 0;
    return(motorSpeed / 11); // 11 is the encoder wheel segmentation : 1 rotation = 11 ticks
  }
  else if(encoderID == 2){
    float motorSpeed = (encoder2_SpeedCounter * 1000)/(millis() - timeMilllisecond);
    timeMilllisecond = millis();
    encoder2_SpeedCounter = 0;
    return(motorSpeed / 11);
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
      return(Encoder1_RotationCounter);
    break;
    case 2 :
      return(encoder2_RotationCounter);
    break;
  }
}

// Encoder 1
static void RotaryIncrementalEncoder::handleInterruptA(){
  // Speed measurement
  if(flagMeasureSpeed){
    encoder1_SpeedCounter++;
  }
  
  // Rotation measurement
  if(flagMeasureRotation){
    if (digitalRead(2) == HIGH) {
      if (digitalRead(3) == LOW) {
        Encoder1_RotationCounter++;
      } else {
        Encoder1_RotationCounter--;
      }
    } else {
      if (digitalRead(3) == LOW) {
        Encoder1_RotationCounter--;
      } else {
        Encoder1_RotationCounter++;
      }
    }
  }
}

// Encoder 2
void RotaryIncrementalEncoder::handleInterruptC(){
  // Speed measurement
  if(flagMeasureSpeed){
    encoder2_SpeedCounter++;
  }
  
  // Rotation measurement
  if(flagMeasureRotation){
    if (digitalRead(18) == HIGH) {
      if (digitalRead(19) == LOW) {
        encoder2_RotationCounter++;
      } else {
        encoder2_RotationCounter--;
      }
    } else {
      if (digitalRead(19) == LOW) {
        encoder2_RotationCounter--;
      } else {
        encoder2_RotationCounter++;
      }
    }
  }
}
