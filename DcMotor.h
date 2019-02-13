/*
 * Class description
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */



#ifndef DcMotor_h
#define DcMotor_h

//*** LIBRARIES ***
#include <arduino.h>
#include "RotaryIncrementalEncoder.h"
#include <AutoPID.h>

class DcMotor
{
  public:
    // Constructor
    DcMotor(uint8_t motorID);

    // Functions
    void setMotorSpeed(uint8_t motorSpeed);
    void setMotorPosition();

  private:
    // Objects

    RotaryIncrementalEncoder* Encoder1;
    AutoPID* myPID;


    // Variables

    uint8_t motorID;
  
    //PID settings and gains
    #define OUTPUT_MIN 0
    #define OUTPUT_MAX 255
    #define KP 10
    #define KI 3
    #define KD 1
    double motorSpeedMeasure, desiredMotorSpeed, outputVal;
    
    // Hardware pinout
    #define speedHardwarePinout 7
};
#endif
