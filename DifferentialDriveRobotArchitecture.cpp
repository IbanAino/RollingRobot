//*** LIBRARIES ***
#include <arduino.h>
#include "DifferentialDriveRobotArchitecture.h"



//*** CONSTRUCTOR ***
DifferentialDriveRobotArchitecture::DifferentialDriveRobotArchitecture(uint8_t wheelRadius, uint8_t distanceWheelCenter, uint8_t reductionRatio){
  motor1 = new DcMotor(1, 28, 29, 7);
  motor2 = new DcMotor(2, 32, 33, 8);
  robotSpeed = 0;
  this -> wheelRadius = wheelRadius;
  this -> distanceWheelCenter = distanceWheelCenter;
  this -> reductionRatio = reductionRatio;
}

//*** FUNCTIONS ***
void DifferentialDriveRobotArchitecture::SetSpeed(uint8_t robotSpeed){
  this -> robotSpeed = robotSpeed;
}

void DifferentialDriveRobotArchitecture::MoveForward(){

  float angularMotorSpeed = LinearSpeedToMotorAngularSpeed(robotSpeed);
  
  motor1 -> setMotorSense(true);
  motor2 -> setMotorSense(true);
  motor1 -> setMotorSpeed(angularMotorSpeed);
  motor2 -> setMotorSpeed(angularMotorSpeed);
}

void DifferentialDriveRobotArchitecture::FollowCurve(float ray, bool trigoSense){
  motor1 -> setMotorSense(true);
  motor2 -> setMotorSense(true);

  float rightSpeed;
  float leftSpeed;
  
  if(trigoSense){
    rightSpeed = ((ray + distanceWheelCenter) / ray) * robotSpeed;
    leftSpeed = ((ray - distanceWheelCenter) / ray) * robotSpeed;
  }else{
    rightSpeed = ((ray - distanceWheelCenter) / ray) * robotSpeed;
    leftSpeed = ((ray + distanceWheelCenter) / ray) * robotSpeed;
  }
  
  motor1 -> setMotorSpeed(LinearSpeedToMotorAngularSpeed(rightSpeed));
  motor2 -> setMotorSpeed(LinearSpeedToMotorAngularSpeed(leftSpeed));
}

float DifferentialDriveRobotArchitecture::LinearSpeedToMotorAngularSpeed(float linearSpeed){
  float wheelAngularSpeed = linearSpeed / (3.14 * 2 * wheelRadius);
  float motorAngularSpeed = wheelAngularSpeed * reductionRatio;
  return(motorAngularSpeed);
}

float* DifferentialDriveRobotArchitecture::GetRobotPosition(float rotationsRight, float rotationsLeft){
  static float robotPosition[3];
  
}
