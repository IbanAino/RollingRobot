/*
 Class description
 
|-------------------------------------------|
|             DcMotor                       |
|-------------------------------------------|
| +DcMotor (uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2)
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
| -uint8_t hardwarePinHStructureIN1;        |
| -uint8_t hardwarePinHStructureIN2;        |
| -static DcMotor* dcMotorObjects[3];       |
| -double desiredMotorSpeed;                |
| -double outputVal;                        |
| -double motorSpeedMeasure;                |
| -static volatile double isrPidOutput;     |
|                                           |
|-------------------------------------------|

*/


#ifndef DcMotor_h
#define DcMotor_h

//*** LIBRARIES ***
#include <arduino.h>
#include "RotaryIncrementalEncoder.h"
#include <AutoPID.h>

// Set Timer2 to run the PID several times per second inside an Interrupt Service Routine
extern "C" void TIMER2_COMPA_vect(void)  __attribute__ ((signal));

class DcMotor
{  
  public:
    //*** CONSTRUCTOR ***
    DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2);

    //*** FUNCTIONS ***
    void setMotorSpeed(uint8_t motorSpeed);
    void setMotorPosition();
    void setMotorSense(bool sense);
    
  private:
    //╔═══ ISR Functions block ═══╗
    friend void TIMER2_COMPA_vect(void);
    static void IsrFunction();
    //╚══════════════════╝

    //*** OBJECTS ***
    RotaryIncrementalEncoder* Encoder;
    AutoPID* myPID;

    //*** VARIABLES ***
    uint8_t motorID;
    uint8_t hardwarePinHStructureIN1;
    uint8_t hardwarePinHStructureIN2;
    static DcMotor* dcMotorObjects[3];
  
    //PID settings and gains
    #define OUTPUT_MIN 0
    #define OUTPUT_MAX 255
    
    #define KP 10
    #define KI .00000001
    #define KD 10
    /*
    #define KP 3
    #define KI .02
    #define KD 0.1
    */
    
    double desiredMotorSpeed;
    double outputVal;
    double motorSpeedMeasure;

    static volatile double isrPidOutput;
    
    // Hardware pinout
    #define hardwarePinoutSpeed 7
};
#endif
