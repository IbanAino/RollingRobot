/*
Class description


*/

#ifndef TricycleRobotArchitecture_h
#define TricycleRobotArchitecture_h

//*** LIBRARIES ***
#include <arduino.h>
#include <Servo.h> 

class TricycleRobotArchitecture
{
  public:
    //*** CONSTRUCTOR ***
    TricycleRobotArchitecture(uint8_t distanceCenterRotaryWheel);

    //*** FUNCTIONS ***
    void FollowCurve(float ray, bool trigoSense);

        float angle;

  private:
    //*** OBJECTS ***
    Servo* servoMotor;
  
    //*** VARIABLES ***
    uint8_t distanceCenterRotaryWheel;

    
};
#endif
