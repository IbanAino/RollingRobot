//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"
#include "DcMotor.h"

//volatile byte state = LOW;

//*** OBJECTS ***

DcMotor* motor1;
//DcMotor* motor2;

//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(115200);
  Serial.println("Start programm");

  motor1 = new DcMotor(1, 28, 29);
  motor1 -> setMotorSense(false);

  //motor2 = new DcMotor(2, 32, 33);
  
  motor1 -> setMotorSpeed(100);
}


//*** MAIN LOOP ***

void loop() {
   //digitalWrite(13, state); 
   motor1 -> setMotorSpeed(100);
}
