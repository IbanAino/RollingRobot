//*** LIBRARIES ***
#include <arduino.h>
#include <math.h>
#include <Servo.h> 
#include "TricycleRobotArchitecture.h"


//*** CONSTRUCTOR ***
TricycleRobotArchitecture::TricycleRobotArchitecture(uint8_t distanceCenterRotaryWheel){
  this -> distanceCenterRotaryWheel = distanceCenterRotaryWheel;
  servoMotor = new Servo();
  servoMotor -> attach(11);
}

//*** FUNCTIONS ***
void TricycleRobotArchitecture::FollowCurve(float ray, bool trigoSense){
  angle = (M_PI / 2) - atan(ray / distanceCenterRotaryWheel);
  float rotationSignal;
  
  if(trigoSense){
    rotationSignal = -854.84 * angle + 1491;
  }else{
    rotationSignal = 854.84 * angle + 1491;
  }
  
  servoMotor -> writeMicroseconds(rotationSignal);
  //servoMotor -> writeMicroseconds(1491);
}
        
