//*** LIBRARIES ***

#include "DifferentialDriveRobotArchitecture.h"


//*** OBJECTS ***

DifferentialDriveRobotArchitecture* robot;


//*** SETUP ***

void setup() {
  Serial.begin(115200);
  
  robot = new DifferentialDriveRobotArchitecture();
  robot -> SetSpeed(100); // speed in mm/s
  robot -> MoveForward();

  Serial.println(robot -> angularWheelSpeed);
}


//*** MAIN LOOP ***

void loop() {
  
}
