/*
 Class description
 
|-------------------------------------------|
|             DcMotor                       |
|-------------------------------------------|
| +DcMotor (uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2, uint8_t hardwarePinHStructurePWM)
| +void setMotorSpeed(uint8_t motorSpeed)   |
| +void setMotorPosition()                  |
| +void setMotorSense(bool sense)           |
|                                           |
| -friend void TIMER2_COMPA_vect(void)      |
| -static void IsrFunction()                |
|                                           |
|-------------------------------------------|
| -RotaryIncrementalEncoder* Encoder        |
| -AutoPID* myPID                           |
| -uint8_t motorID;                         |
| -uint8_t hardwarePinHStructureIN1         |
| -uint8_t hardwarePinHStructureIN2         |
| -uint8_t hardwarePinHStructurePWM         |
| -static DcMotor* dcMotorObjects[3]        |
| -double desiredMotorSpeed;                |
| -double outputVal;                        |
| -double motorSpeedMeasure;                |
|                                           |
|-------------------------------------------|

*/


#ifndef DcMotor_h
#define DcMotor_h


//*** LIBRARIES ***

#include <arduino.h>
#include "RotaryIncrementalEncoder.h"
#include "PidController.h"

// Set Timer2 to run the PID several times per second inside an Interrupt Service Routine
extern "C" void TIMER2_COMPA_vect(void)  __attribute__ ((signal));

class DcMotor
{  
  public:
    //*** CONSTRUCTOR ***
    DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2, uint8_t hardwarePinHStructurePWM);

    //*** FUNCTIONS ***
    void setMotorSpeed(float motorSpeed); // speed in rotations/second
    void setMotorPosition();
    void setMotorSense(bool sense);
    
  private:
    //╔═══ ISR Functions block ═══╗
    friend void TIMER2_COMPA_vect(void);
    static void IsrFunction();
    //╚══════════════════╝

    //*** OBJECTS ***
    RotaryIncrementalEncoder* Encoder;
    PidController* MyPidController;

    //*** VARIABLES ***
    uint8_t motorID;
    uint8_t hardwarePinHStructureIN1;
    uint8_t hardwarePinHStructureIN2;
    uint8_t hardwarePinHStructurePWM;
    static DcMotor* dcMotorObjects[3];
};
#endif
