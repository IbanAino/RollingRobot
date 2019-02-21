/*
The PidController class implements PID computations.
This PID does not have any time manager because its functions are supposed to be called through an Interrupt Service Routine.
*/

/*
 Class description
 
|-------------------------------------------|
|             PidController                 |
|-------------------------------------------|
| +PidController(float kP, float kI, float kD, float outputMin, float outputMax)
| +float SetSetPoint(float setPoint)        |
| +float Compute(float measurement)         |
|                                           |
|-------------------------------------------|
| -float kP                                 |
| -float kI                                 |
| -float kD                                 |
| -float setPoint                           |
| -float outputMin                          |
| -float outputMax                          |
| -float outputVal                          |
|                                           |
|-------------------------------------------|

*/


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
