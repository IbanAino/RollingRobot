//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"
#include "DcMotor.h"



//*** OBJECTS ***

DcMotor* motor1;


//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

  motor1 = new DcMotor(1, 28, 29);
  motor1 -> setMotorSense(false);
}


//*** MAIN LOOP ***

void loop() {
  motor1 -> setMotorSpeed(120);
}
