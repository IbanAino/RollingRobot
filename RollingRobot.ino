//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"


//*** VARIABLES ***

// Communication PC to arduino
int incomingByte = 0;   // for incoming serial data
int finalMessageSended = 0;

// Initialize static members of class RotaryIncrementalEncoder.
// This step is needed because the RotaryIncrementalEncoder uses interrupts with static
// methods and members.

uint16_t RotaryIncrementalEncoder::encoder1_SpeedCounter;
uint16_t RotaryIncrementalEncoder::encoder2_SpeedCounter;
int16_t RotaryIncrementalEncoder::encoder1_RotationCounter;
int16_t RotaryIncrementalEncoder::encoder2_RotationCounter;
bool RotaryIncrementalEncoder::flagMeasureSpeed;
bool RotaryIncrementalEncoder::flagMeasureRotation;

//PID settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 10
#define KI 3
#define KD 1
double motorSpeedMeasure, desiredMotorSpeed, outputVal;

// Hardware pinout
uint8_t speedHardwarePinout = 7;


//*** OBJECTS DECLARATIONS ***

RotaryIncrementalEncoder* Encoder1;

//input/output variables passed by reference, so they are updated automatically
AutoPID myPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);


//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

  // Objects instanciations
  Encoder1 = new RotaryIncrementalEncoder(1);
  
  Encoder1->StartSpeedMeasurement();

  pinMode(speedHardwarePinout, OUTPUT);

  desiredMotorSpeed = 100;

  //myPID.setBangBang(100);

  myPID.setTimeStep(2);
}


//*** MAIN LOOP ***

void loop() {
  // Listen the computer to get the speed order
  /*
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  
    if(incomingByte == 0xA){
      desiredMotorSpeed = finalMessageSended;
      finalMessageSended = 0;
      //Serial.println(desiredMotorSpeed);
    }else if(0x29 < incomingByte < 0x3A){ // incomingByte between 0 and 9
      finalMessageSended = (finalMessageSended * 10) + (incomingByte - 0x30);
    }   
  }
  */

  motorSpeedMeasure = Encoder1->GetSpeed(); 
  myPID.run();
  analogWrite(speedHardwarePinout, outputVal);
  //analogWrite(speedHardwarePinout, 50);
  
  Serial.print(desiredMotorSpeed);
  Serial.print(", ");
  Serial.print(motorSpeedMeasure);
  Serial.print(", ");
  Serial.print(outputVal);
    Serial.print(", ");
  Serial.print(desiredMotorSpeed - motorSpeedMeasure);
  Serial.println();

 

  //delay(100);
}
