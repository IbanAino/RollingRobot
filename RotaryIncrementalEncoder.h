/*
The Rotary Incremental Encoder class implements encoders.

This class is made for the Arduino Mega 2560 board.
The first encoder is plugged on pins 2 and 3.
The sescond encoder is plugged on pins 18 and 19.
You can change this values inside the cpp file.
You can upgrade this code to add a third encoder, plugged on pins 20 and 21.

|-----------|->pin2
| Encoder 1 |->pin3
|-----------|

|-----------|->pin18
| Encoder 2 |->pin19
|-----------|

*/

/*
 Class description
 
|-------------------------------------------|
|       RotaryIncrementalEncoder            |
|-------------------------------------------|
| +RotaryIncrementalEncoder(uint8_t encoderID)
| +void StartSpeedMeasurement()             |
| +void StopSpeedMeasurement()              |
| +int16_t GetSpeed()                       |
| +void StartRotationMeasurement()          |
| +void StopRotationMeasurement()           |
| +int16_t GetRotation()                    |
|                                           |
| -static void handleInterruptA();          |
| -static void handleInterruptC();          |
|                                           |
|-------------------------------------------|
| -uint8_t encoderID;                       |
| -uint8_t hardwarePinEncoderSensorA;       |
| -uint8_t hardwarePinEncoderSensorB;       |
| -uint8_t hardwarePinEncoderSensorC;       |
| -uint8_t hardwarePinEncoderSensorD;       |
| -unsigned long timeMilllisecond;          |
| -static int16_t Encoder1_RotationCounter; |
| -static int16_t encoder2_RotationCounter; |
| -static uint16_t encoder1_SpeedCounter;    |
| -static uint16_t encoder2_SpeedCounter;   |
| -static bool flagMeasureSpeed;            |
| -static bool flagMeasureRotation;         |
|                                           |
|-------------------------------------------|

*/


#ifndef RotaryIncrementalEncoder_h
#define RotaryIncrementalEncoder_h

//*** LIBRARIES ***
#include <arduino.h>

class RotaryIncrementalEncoder
{
  public:
    //*** CONSTRUCTOR ***
    RotaryIncrementalEncoder(uint8_t encoderID);

    //*** FUNCTIONS ***
    // Velocity
    void StartSpeedMeasurement();
    void StopSpeedMeasurement();
    float GetSpeed(); // Result in rotations per seconds

    // Rotation
    void StartRotationMeasurement();
    void StopRotationMeasurement();
    int16_t GetRotation();

  private:
    // Static functions
    static void handleInterruptA();
    static void handleInterruptC();
 
     //*** VARIABLES ***
    uint8_t encoderID;
     
    uint8_t hardwarePinEncoderSensorA;
    uint8_t hardwarePinEncoderSensorB;
    uint8_t hardwarePinEncoderSensorC;
    uint8_t hardwarePinEncoderSensorD;

    // Time scheduler to compute speed
    unsigned long timeMilllisecond;

    // Static members   
    static int16_t Encoder1_RotationCounter;
    static int16_t encoder2_RotationCounter;
    static uint16_t encoder1_SpeedCounter;
    static uint16_t encoder2_SpeedCounter;
    static bool flagMeasureSpeed; 
    static bool flagMeasureRotation;
};
#endif
