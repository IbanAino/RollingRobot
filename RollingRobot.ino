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
  robotDifferentialDrive -> SetSpeed(120); // speed in mm/s
  //robotDifferentialDrive -> MoveForward();
  robotDifferentialDrive -> FollowCurve(600, false);

  robotTricycle = new TricycleRobotArchitecture(98);
  robotTricycle -> FollowCurve(600, false);
  //Serial.println(robotTricycle -> angle);
  
}


//*** MAIN LOOP ***

void loop() {
  
}
