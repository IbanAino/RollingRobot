//*** LIBRARIES ***

#include "DifferentialDriveRobotArchitecture.h"


//*** OBJECTS ***

DifferentialDriveRobotArchitecture* robot;


//*** SETUP ***

void setup() {
  Serial.begin(115200);
  
  robot = new DifferentialDriveRobotArchitecture(32, 74, 64);
  robot -> SetSpeed(100); // speed in mm/s
  //robot -> MoveForward();
  robot -> FollowCurve(300, false);
}


//*** MAIN LOOP ***

void loop() {
  
}
