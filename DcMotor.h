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


extern "C" void TIMER2_COMPA_vect(void)  __attribute__ ((signal));

class DcMotor
{  
  public:
    // Constructor
    DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2);

    // Functions
    void setMotorSpeed(uint8_t motorSpeed);
    void setMotorPosition();
    void setMotorSense(bool sense);

    // Static function
    friend void TIMER2_COMPA_vect(void);

  private:
    // Objects

    RotaryIncrementalEncoder* Encoder1;
    AutoPID* myPID;


    // Variables

    uint8_t motorID;
    uint8_t hardwarePinHStructureIN1;
    uint8_t hardwarePinHStructureIN2;
  
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
    
    double motorSpeedMeasure, desiredMotorSpeed, outputVal;
    
    // Hardware pinout
    #define hardwarePinoutSpeed 7
};
#endif
