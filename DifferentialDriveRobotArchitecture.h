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
    void FollowCurve(float ray, bool trigoSense); // ray in mm
  
  
  private:
    float LinearSpeedToMotorAngularSpeed(float linearSpeed);

  
    //*** OBJECTS ***
    DcMotor* motor1;
    DcMotor* motor2;
  
  
    //*** VARIABLES ***
    // Robot hardware caracteristics :
    uint8_t wheelRadius;
    uint8_t distanceWheelCenter;
    uint8_t reductionRatio;
    
    uint8_t robotSpeed;

};    

#endif
