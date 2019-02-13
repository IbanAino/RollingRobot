//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"
#include "DcMotor.h"


//*** VARIABLES ***
/*
// Communication PC to arduino
int incomingByte = 0;   // for incoming serial data
int finalMessageSended = 0;
*/
// Initialize static members of class RotaryIncrementalEncoder.
// This step is needed because the RotaryIncrementalEncoder uses interrupts with static
// methods and members.
// Because thos class is instanciated several times we have to avoid declaring those variables several times.
// That is why we uses compilator orders



//PID settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 10
#define KI 3
#define KD 1
double motorSpeedMeasure, desiredMotorSpeed, outputVal;

// Hardware pinout
//uint8_t speedHardwarePinout = 7;


//*** OBJECTS DECLARATIONS ***
/*
RotaryIncrementalEncoder* Encoder1;

//input/output variables passed by reference, so they are updated automatically
AutoPID myPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

*/

DcMotor* motor1;

//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

/*
  // Objects instanciations
  Encoder1 = new RotaryIncrementalEncoder(1);
  
  Encoder1->StartSpeedMeasurement();

  pinMode(speedHardwarePinout, OUTPUT);

  desiredMotorSpeed = 180;

  //myPID.setBangBang(100);

  myPID.setTimeStep(2);
  */
  motor1 = new DcMotor(1);
}


//*** MAIN LOOP ***

void loop() {

  motor1 -> setMotorSpeed(150);
  //analogWrite(7, 150);
  /*
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
  */
}
