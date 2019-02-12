//*** LIBRARIES ***
#include <AutoPID.h>
#include "RotaryIncrementalEncoder.h"

// Initialize static members of class RotaryIncrementalEncoder.
// This step is needed because the RotaryIncrementalEncoder uses interrupts with static
// methods and members.
int16_t RotaryIncrementalEncoder::encoderRotationRightCounter;
int16_t RotaryIncrementalEncoder::encoderRotationLeftCounter;
uint16_t RotaryIncrementalEncoder::encoderSpeedRightCounter;
uint16_t RotaryIncrementalEncoder::encoderSpeedLeftCounter;
bool RotaryIncrementalEncoder::flagMeasureSpeed;
bool RotaryIncrementalEncoder::flagMeasureRotation;

//*** OBJECTS DECLARATIONS ***
RotaryIncrementalEncoder* Encoder1;
RotaryIncrementalEncoder* Encoder2;

//*** SETUP ***
void setup() {
  // Serial communicaiton with PC
  Serial.begin(9600);
  Serial.println("Start programm");

  // Objects instanciations
  Encoder1 = new RotaryIncrementalEncoder(1);
  Encoder2 = new RotaryIncrementalEncoder(2);
  
  Encoder1->StartSpeedMeasurement();
  Encoder2->StartSpeedMeasurement();
}

void loop() {
  Serial.print(Encoder1->GetSpeed());
  Serial.print(", ");
  Serial.print(Encoder2->GetSpeed());
  Serial.println();

  delay(100);

}
