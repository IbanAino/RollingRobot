//*** LIBRARIES ***

#include "DifferentialDriveRobotArchitecture.h"
#include "TricycleRobotArchitecture.h"

//*** OBJECTS ***

DifferentialDriveRobotArchitecture* robotDifferentialDrive;
TricycleRobotArchitecture* robotTricycle;


//*** SETUP ***

void setup() {
  Serial.begin(115200);
  
  robotDifferentialDrive = new DifferentialDriveRobotArchitecture(32, 74, 64);  
  robotDifferentialDrive -> SetSpeed(60); // speed in mm/s
  robotDifferentialDrive -> MoveForward();
  //robotDifferentialDrive -> FollowCurve(100, false);

  robotTricycle = new TricycleRobotArchitecture(113);
  //robotTricycle -> FollowCurve(100, true);
  //Serial.println(robotTricycle -> angle);
  robotTricycle -> goStraight();
  
}


//*** MAIN LOOP ***

void loop() {
  
}
