//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"


//*** VARIABLES ***

// Initialize static members of class RotaryIncrementalEncoder.
// This step is needed because the RotaryIncrementalEncoder uses interrupts with static
// methods and members.
int16_t RotaryIncrementalEncoder::encoderRotationRightCounter;
int16_t RotaryIncrementalEncoder::encoderRotationLeftCounter;
uint16_t RotaryIncrementalEncoder::encoderSpeedRightCounter;
uint16_t RotaryIncrementalEncoder::encoderSpeedLeftCounter;
bool RotaryIncrementalEncoder::flagMeasureSpeed;
bool RotaryIncrementalEncoder::flagMeasureRotation;

//PID settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 1
#define KI .0003
#define KD 0
double motorSpeedMeasure, desiredMotorSpeed, outputVal;

// Communication PC to arduino
int incomingByte = 0;   // for incoming serial data
int finalMessageSended = 0;

//*** OBJECTS DECLARATIONS ***

RotaryIncrementalEncoder* Encoder1;
//RotaryIncrementalEncoder* Encoder2;

//input/output variables passed by reference, so they are updated automatically
AutoPID myPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);


//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

  // Objects instanciations
  Encoder1 = new RotaryIncrementalEncoder(1);
  //Encoder2 = new RotaryIncrementalEncoder(2);
  
  Encoder1->StartSpeedMeasurement();
  //Encoder2->StartSpeedMeasurement();
}


//*** MAIN LOOP ***

void loop() {
  // Listen the computer to get the speed order
  if (Serial.available() > 0) {
        incomingByte = Serial.read();

        if(incomingByte == 0xA){
          desiredMotorSpeed = finalMessageSended;
          finalMessageSended = 0;
          Serial.println(desiredMotorSpeed);
        }else if(0x29 < incomingByte < 0x3A){ // incomingByte between 0 and 9
          finalMessageSended = (finalMessageSended * 10) + (incomingByte - 0x30);
        }   
  }

  Serial.print(Encoder1->GetSpeed());
  //Serial.print(", ");
  //Serial.print(Encoder2->GetSpeed());
  Serial.println();

  delay(100);
}
