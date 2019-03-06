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
  float angle = (M_PI / 2) - atan(ray / distanceCenterRotaryWheel);
  float rotationSignal;
  
  if(trigoSense){
    rotationSignal = -888.721387 * angle + 1480;
  }else{
    rotationSignal = 888.721387 * angle + 1480;
  }
  
  servoMotor -> writeMicroseconds(rotationSignal);
  //servoMotor -> writeMicroseconds(1480);
}

void TricycleRobotArchitecture::goStraight(){
  servoMotor -> writeMicroseconds(1480);
}
        
