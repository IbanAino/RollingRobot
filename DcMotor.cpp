/* 
REGISTERS DOCUMENTATION FOR TIMER2 :
  
  TIMSK2 :
       7      6      5      4      3      2      1      0
    |------|------|------|------|------|------|------|------|       TIMSK2 = TImer MaSK, timer n°2
        -      -      -      -      -   OCIE2B OCIE2A TOIE2         OCIE = Output Compatator Interrupt Enable
    |------|------|------|------|------|------|------|------|       TOIE = Timer Overflow Interrupt Enable
        R      R      R      R     R     R/W    R/W    R/W
  
  TCCR2A :
       7      6      5      4      3      2      1      0
    |------|------|------|------|------|------|------|------|       TCCR2A = Timer Counter Control Register, timer n°2, register A
     COM2A1 COM2A0 COM2B1 COM2B0   -      -    WGM21  WGM20         COM = Compare Output Mode
    |------|------|------|------|------|------|------|------|       WGM = Wave Generator Mode
       R/W    R/W   R/W    R/W     R      R    R/W    R/W
  
  TCCR2B :
       7      6      5      4      3      2      1      0
    |------|------|------|------|------|------|------|------|       TCCR2B = Timer Counter Control Register, timer n°2, register B
     FOC2A  FOC2B     -      -   WGM22   CS22   CS21   CS20         FOC = 
    |------|------|------|------|------|------|------|------|       WGM = Wave Generator Mode
        W      W      R      R    R/W    R/W    R/W    R/W          CS = Clock Selector
*/


//*** LIBRARIES ***

#include "DcMotor.h"
#include <arduino.h>
#include "PidController.h"


//*** Static variables declarations ***

DcMotor* DcMotor::dcMotorObjects[3];


//*** CONSTRUCTOR ***

DcMotor::DcMotor(uint8_t motorID, uint8_t hardwarePinHStructureIN1, uint8_t hardwarePinHStructureIN2, uint8_t hardwarePinHStructurePWM){

  this -> motorID = motorID; // Two motors availables : motor 1 and motor 2
  this -> hardwarePinHStructureIN1 = hardwarePinHStructureIN1;
  this -> hardwarePinHStructureIN2 = hardwarePinHStructureIN2;
  this -> hardwarePinHStructurePWM = hardwarePinHStructurePWM;

  // Set motor sense to stop
  pinMode(hardwarePinHStructureIN1, OUTPUT);
  pinMode(hardwarePinHStructureIN2, OUTPUT);
  digitalWrite(hardwarePinHStructureIN1, LOW);
  digitalWrite(hardwarePinHStructureIN2, LOW);

  // Set encoder and PID
  Encoder = new RotaryIncrementalEncoder(motorID);
  Encoder->StartSpeedMeasurement();
  MyPidController = new PidController(0.2, 0.001, 3, 0, 255);

  //╔═══ ISR settings block ═══╗
  // Set Timer2 to run the PID several times per second inside an Interrupt Service Routine
  // THE TIMER IS SET TO 30 Hz
  pinMode(13, OUTPUT);
  DDRH |= (1<<6); // pinMode 9 output
  DDRB |= (1<<4); // pinmode 10 output
  
  TIMSK2 = (0<<OCIE2B) | (1<<OCIE2A) | (0<<TOIE2);
  TCCR2A = (0<<COM2A0) | (1<<COM2A1)| (0<<COM2B0) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);

  OCR2A = 200;   // OCRx - Output Compare Register
  OCR2B = 100;

  dcMotorObjects[motorID] = this;
  //╚══════════════════╝
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

void DcMotor::setMotorSpeed(float motorSpeed){
  MyPidController -> SetSetPoint(motorSpeed);
}

float DcMotor::GetMotorRotations(){
  return (Encoder -> GetRotation());
}

void DcMotor::ResetMotorRotationsCounter(){
  Encoder -> ResetRotationsCounter();
}

//╔═══ ISR Functions block ═══╗
void DcMotor::IsrFunction(){
  digitalWrite(13, digitalRead(13) ^ 1);
  // Call all of the DcMotor objects instanciated stored in the array dcMotorObjects
  for(uint8_t i = 1; i < 3; i++){
    if(dcMotorObjects[i] != NULL){
      analogWrite(dcMotorObjects[i]->hardwarePinHStructurePWM, dcMotorObjects[i]->MyPidController->Compute(dcMotorObjects[i]->Encoder->GetSpeed()));
    }
  }
}

ISR(TIMER2_COMPA_vect){
  DcMotor::IsrFunction(); // Calls the function above↑
}
//╚══════════════════╝
