//*** LIBRARIES ***

#include "DcMotor.h"
#include <arduino.h>
#include <AutoPID.h>



//*** CONSTRUCTOR ***

DcMotor::DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2){

  this -> motorID = motorID; // Two motors availables : motor 1 and motor 2
  this -> hardwarePinHStructureIN1 = hardwarePinHStructureIN1;
  this -> hardwarePinHStructureIN2 = hardwarePinHStructureIN2;

  // Set motor sense to stop
  pinMode(hardwarePinHStructureIN1, OUTPUT);
  pinMode(hardwarePinHStructureIN2, OUTPUT);
  digitalWrite(hardwarePinHStructureIN1, LOW);
  digitalWrite(hardwarePinHStructureIN2, LOW);

  // Set encoder and PID
  Encoder1 = new RotaryIncrementalEncoder(motorID);
  myPID = new AutoPID(&motorSpeedMeasure, &desiredMotorSpeed, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
  //myPID->setTimeStep(2);
  //myPID->setBangBang(100);
  Encoder1->StartSpeedMeasurement();


  //═══ ISR settings block ═══
  // Set Timer2 to run the PID several times per second inside an Interrupt Service Routine
  
  TIMSK2 = (TIMSK2 & B11111001) | 0x06;    // TIMSKx - Timer/Counter Interrupt Mask Register. To enable/disable timer interrupts.
  //    7      6      5      4      3     2      1     0
  //┌───┬───┬───┬───┬───┬───┬───┬───┐
  //    -      -      -      -      -   OCIE2B OCIE2A TOIE2     TIMSK2 (ATMEGA 2560)    OCIE = Output Compatator Interrupt Enable
  //└───┴───┴───┴───┴───┴───┴───┴───┘                            TOIE = Timer Overflow Interrupt Enable
  //    R      R      R      R     R     R/W    R/W    R/W

  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // TCCRx - Timer/Counter Control Register. The pre-scaler can be configured here.
  //    7      6      5      4      3     2      1     0
  //┌───┬───┬───┬───┬───┬───┬───┬───┐
  // COM2A1 COM2A0 COM2B1 COM2B0   -      -   CWGM21  WGM20     TTCR2A (ATMEGA 2560)
  //└───┴───┴───┴───┴───┴───┴───┴───┘
  //    W      W      R      R    R/W    R/W    R/W    R/W
  
   
  TCCR2B = (TCCR2B & B11111000) | 0x07; // TCCRx - Timer/Counter Control Register. The pre-scaler can be configured here.
  //    7      6      5      4      3     2      1     0
  //┌───┬───┬───┬───┬───┬───┬───┬───┐
  //  FOC2A  FOC2B    -      -    WGM22  CS22   CS21   CS20      TTCR2B (ATMEGA 2560)
  //└───┴───┴───┴───┴───┴───┴───┴───┘
  //    W      W      R      R    R/W    R/W    R/W    R/W
   
  OCR2A = 180;   // OCRx - Output Compare Register
  OCR2B = 30;

  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  //══════════════════
}


//*** FUNCTIONS ***

void DcMotor::setMotorSense(bool sense){
  if(sense){
    digitalWrite(hardwarePinHStructureIN1, HIGH);
    digitalWrite(hardwarePinHStructureIN2, LOW);
  }else{
    digitalWrite(hardwarePinHStructureIN1, LOW);
    digitalWrite(hardwarePinHStructureIN2, HIGH);
  }
}

void DcMotor::setMotorSpeed(uint8_t motorSpeed){

  desiredMotorSpeed = motorSpeed;
  motorSpeedMeasure = Encoder1->GetSpeed(); 
  //myPID->run();
  analogWrite(hardwarePinoutSpeed, outputVal);
/*
  Serial.print(desiredMotorSpeed);
  Serial.print(", ");
  Serial.print(motorSpeedMeasure);
  Serial.print(", ");
  Serial.print(outputVal);
  Serial.print(", ");
  Serial.print(desiredMotorSpeed - motorSpeedMeasure);
  Serial.println();
  */
}

//═══ ISR Functions block ═══
void DcMotor::IsrFunction(){
  digitalWrite(13, digitalRead(13) ^ 1);
}

ISR(TIMER2_COMPA_vect){
  DcMotor::IsrFunction();
}
//══════════════════
