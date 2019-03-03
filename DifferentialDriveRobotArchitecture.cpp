//*** LIBRARIES ***
#include <arduino.h>
#include "DifferentialDriveRobotArchitecture.h"


//*** CONSTRUCTOR ***
DifferentialDriveRobotArchitecture::DifferentialDriveRobotArchitecture(){
  motor1 = new DcMotor(1, 28, 29, 7);
  motor2 = new DcMotor(2, 32, 33, 8);
  robotSpeed = 0;
  wheelRadius = 32;
  distanceBetweenWheels = 148;
}

//*** FUNCTIONS ***
void DifferentialDriveRobotArchitecture::SetSpeed(uint8_t robotSpeed){
  this -> robotSpeed = robotSpeed;
}

void DifferentialDriveRobotArchitecture::MoveForward(){
  // Compute motor speed from global robot speed
  angularWheelSpeed = robotSpeed / (3.14 * 2 * wheelRadius);
  
  motor1 -> setMotorSense(true);
  motor2 -> setMotorSense(true);
  motor1 -> setMotorSpeed(angularWheelSpeed * 40);
  motor2 -> setMotorSpeed(angularWheelSpeed * 40);
  //motor1 -> setMotorSpeed(100);
  //motor2 -> setMotorSpeed(20);
}

void DifferentialDriveRobotArchitecture::FollowCurve(uint16_t ray, bool trigoSense){
  uint8_t rightSpeed;
  uint8_t leftSpeed;
  
}
