//*** LIBRARIES ***
#include <arduino.h>
#include "DifferentialDriveRobotArchitecture.h"


//*** CONSTRUCTOR ***
DifferentialDriveRobotArchitecture::DifferentialDriveRobotArchitecture(){
  motor1 = new DcMotor(1, 28, 29, 7);
  motor2 = new DcMotor(2, 32, 33, 8);
  robotSpeed = 0;
}

//*** FUNCTIONS ***
void DifferentialDriveRobotArchitecture::SetSpeed(uint8_t robotSpeed){
  this -> robotSpeed = robotSpeed;
}

void DifferentialDriveRobotArchitecture::MoveForward(){
  motor1 -> setMotorSense(true);
  motor2 -> setMotorSense(true);
  motor1 -> setMotorSpeed(robotSpeed);
  motor2 -> setMotorSpeed(robotSpeed);
}

void DifferentialDriveRobotArchitecture::FollowCurve(uint16_t ray, bool trigoSense){

  
}
