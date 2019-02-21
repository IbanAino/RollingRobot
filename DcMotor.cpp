// REGISTERS DOCUMENTATION FOR TIMER2

  // TIMSK2
  //   7      6      5      4      3      2      1      0
  //|------|------|------|------|------|------|------|------|
  //    -      -      -      -      -   OCIE2B OCIE2A TOIE2     TIMSK2 (ATMEGA 2560)    OCIE = Output Compatator Interrupt Enable
  //|------|------|------|------|------|------|------|------|                           TOIE = Timer Overflow Interrupt Enable
  //    R      R      R      R     R     R/W    R/W    R/W

  // TCCR2A 
  //    7      6      5      4      3     2      1     0
  //┌───┬───┬───┬───┬───┬───┬───┬───┐
  // COM2A1 COM2A0 COM2B1 COM2B0   -      -    WGM21  WGM20     TCCR2A (ATMEGA 2560)
  //└───┴───┴───┴───┴───┴───┴───┴───┘
  //   R/W    R/W   R/W    R/W     R      R    R/W    R/W

  // TCCR2B
  //    7      6      5      4      3     2      1     0
  //┌───┬───┬───┬───┬───┬───┬───┬───┐
  //  FOC2A  FOC2B    -      -   WGM22   CS22   CS21   CS20      TCCR2B (ATMEGA 2560)
  //└───┴───┴───┴───┴───┴───┴───┴───┘
  //    W      W      R      R    R/W    R/W    R/W    R/W

//*** LIBRARIES ***

#include "DcMotor.h"
#include <arduino.h>
#include <AutoPID.h>


//*** Static variables declarations ***
DcMotor* DcMotor::dcMotorObjects[3];
double volatile DcMotor::isrPidOutput = 40;
/*
double DcMotor::outputVal;
double DcMotor::motorSpeedMeasure;
double DcMotor::desiredMotorSpeed;
*/

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
  myPID->setTimeStep(10);
  myPID->setBangBang(100);
  Encoder1->StartSpeedMeasurement();


  //╔═══ ISR settings block ═══╗
  // Set Timer2 to run the PID several times per second inside an Interrupt Service Routine
  pinMode(13, OUTPUT);
  DDRH |= (1<<6); // pinMode 9 output
  DDRB |= (1<<4); // pinmode 10 output
  
  TIMSK2 = (0<<OCIE2B) | (1<<OCIE2A) | (0<<TOIE2);
  TCCR2A = (0<<COM2A0) | (1<<COM2A1)| (0<<COM2B0) | (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);

  OCR2A = 200;   // OCRx - Output Compare Register
  OCR2B = 100;

  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);

  dcMotorObjects[motorID] = this;
  outputVal = 100;
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

void DcMotor::setMotorSpeed(uint8_t motorSpeed){

  //desiredMotorSpeed = motorSpeed;
  //motorSpeedMeasure = Encoder1->GetSpeed(); 
  //myPID->run();
  //analogWrite(hardwarePinoutSpeed, outputVal);
  Serial.println(outputVal);
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

//╔═══ ISR Functions block ═══╗
void DcMotor::IsrFunction(){
  digitalWrite(13, digitalRead(13) ^ 1);
  // Call all of the DcMotor objects instanciated stored in the array dcMotorObjects
  /*
  for(uint8_t i = 0; i < 4; i++){
    if(dcMotorObjects[i] != NULL){
      // Get current speed :
      dcMotorObjects[i]->motorSpeedMeasure = 10;
      // Compute PID :
      dcMotorObjects[i]->myPID->run();
      // Control the motor :
      analogWrite(7, dcMotorObjects[i]->outputVal);
    }
  }*/
        // Get current speed :
      //dcMotorObjects[1]->motorSpeedMeasure = 60;
      // Compute PID :
      //dcMotorObjects[1]->myPID->run();
      // Control the motor :
      //analogWrite(7, dcMotorObjects[1]->outputVal);
      //analogWrite(7, dcMotorObjects[1]->motorSpeedMeasure);

    //dcMotorObjects[1]->motorSpeedMeasure = dcMotorObjects[1]->Encoder1->GetSpeed();

    double speedMotor = dcMotorObjects[1]->Encoder1->GetSpeed();
    speedMotor = 130;
    double error = 120 - speedMotor;
    
    dcMotorObjects[1]->outputVal = dcMotorObjects[1]->outputVal + 1;

    double out = dcMotorObjects[1]->outputVal;
    
    isrPidOutput++;
    
    if(out < 0){
      out = 0;
    }
    if(out > 255){
      out = 255;
    }

    analogWrite(7, isrPidOutput);
}

ISR(TIMER2_COMPA_vect){
  DcMotor::IsrFunction(); // Calls the function above↑
}
//╚══════════════════╝
