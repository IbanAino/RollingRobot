//*** LIBRARIES ***

#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"
#include "DcMotor.h"

//volatile byte state = LOW;

//*** OBJECTS ***

DcMotor* motor1;
DcMotor* motor2;

//*** SETUP ***

void setup() {
  // Serial communicaiton with PC
  Serial.begin(115200);
  Serial.println("Start programm");

  motor1 = new DcMotor(1, 28, 29, 7);
  motor1 -> setMotorSense(true);
  motor1 -> setMotorSpeed(120);

  motor2 = new DcMotor(2, 32, 33, 8);
  motor2 -> setMotorSense(false);
  motor2 -> setMotorSpeed(100);
}


//*** MAIN LOOP ***

void loop() {

}
