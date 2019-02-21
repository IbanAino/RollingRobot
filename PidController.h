#ifndef PidController_h
#define PidController_h

//*** LIBRARIES ***
#include <arduino.h>

class PidController
{
  public:
    //*** CONSTRUCTOR ***
    PidController(float kP, float kI, float kD, float outputMin, float outputMax);
    
    //*** FUNCTIONS ***
    float SetSetPoint(float setPoint);
    float Compute(float measurement);

  private:
    //*** VARIABLES ***
    float kP;
    float kI;
    float kD;
    float setPoint;
    float outputMin;
    float outputMax;
    float outputVal;
};
#endif
