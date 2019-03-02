/*
Class description


*/


#ifndef DifferentialDriveRobotArchitecture_h
#define DifferentialDriveRobotArchitecture_h

//*** LIBRARIES ***
#include <arduino.h>
#include "DcMotor.h"

class DifferentialDriveRobotArchitecture
{  
  public:
  //*** CONSTRUCTOR ***
  DifferentialDriveRobotArchitecture();

  //*** FUNCTIONS ***
  void SetSpeed(uint8_t robotSpeed);
  void MoveForward();
  void FollowCurve(uint16_t ray, bool trigoSense);
  
  
  private:
  //*** OBJECTS ***
  DcMotor* motor1;
  DcMotor* motor2;


  //*** VARIABLES ***
  uint8_t robotSpeed;

};    

#endif
