//*** LIBRARIES ***

#include "DifferentialDriveRobotArchitecture.h"


//*** OBJECTS ***

DifferentialDriveRobotArchitecture* robot;


//*** SETUP ***

void setup() {
  robot = new DifferentialDriveRobotArchitecture();
  robot -> SetSpeed(100);
  robot -> MoveForward();
}


//*** MAIN LOOP ***

void loop() {
  
}
