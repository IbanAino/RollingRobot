/*
The Rotary Incremental Encoder class implements encodrs.


// WARNING :
This class uses iterrupts with staic methods and members.
That is why static members have to be declared when the class is instancied.
It is the only particularitie you have to deal with.


This class is optimize to the Arduino Mega 2560 board.
The first encoder is plugged to pins 2 and 3.
The sescond encoder is plugged to pins 18 and 19.
You can change this values inside the cpp file.
You can upgrade the code to add a third encoder, plugged to pins 20 and 21.
*/

#ifndef RotaryIncrementalEncoder_h
#define RotaryIncrementalEncoder_h

#include <arduino.h>

class RotaryIncrementalEncoder
{
  public:
    // Constructor
    RotaryIncrementalEncoder(uint8_t encoderID);

    // Functions

    // Velocity
    void StartSpeedMeasurement();
    void StopSpeedMeasurement();
    int16_t GetSpeed(); // Result in rotations per seconds

    // Rotation
    void StartRotationMeasurement();
    void StopRotationMeasurement();
    int16_t GetRotation();

    // Static functions
    static void handleInterruptA();
    static void handleInterruptC();
 
  private:
     // Attributs
    uint8_t encoderID;
     
    uint8_t hardwarePinEncoderSensorA;
    uint8_t hardwarePinEncoderSensorB;
    uint8_t hardwarePinEncoderSensorC;
    uint8_t hardwarePinEncoderSensorD;

    // Time scheduler to compute speed
    unsigned long timeMilllisecond;

    // Static members
    static int16_t encoder1_RotationCounter;
    static int16_t encoder2_RotationCounter;
    static uint16_t encoder1_SpeedCounter;
    static uint16_t encoder2_SpeedCounter;
    static bool flagMeasureSpeed; 
    static bool flagMeasureRotation;   
};
#endif
