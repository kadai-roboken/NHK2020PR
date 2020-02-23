#include "Arduino.h"
#include "DegSensor.h"

void DegSensor::Trace(int TraceHold){
  r = senR->Trace(R_DA,TraceHold);
  l = senL->Trace(L_DA,TraceHold);
  f = senF->Trace(F_DA,TraceHold);
  b = senB->Trace(B_DA,TraceHold);
}

float DegSensor::TraceAng(int TraceHold){
//  return 1*(degsen->Trace(TraceHold) - 0.5)/0.5;
//  return degsen->MAX();
  Trace(TraceHold);
  return -atan2(r - l,f - b)*180/PI;

}

float DegSensor::TraceDis(int TraceHold){
  Trace(TraceHold);
  return sqrt((r - l)*(r -l)+(f - b)*(f - b))/sqrt(2);
}

void DegSensor::Print(){
  Serial.print(F("R{"));
  senR->Print();
  Serial.print(F("} L{"));
  senL->Print();
  Serial.print(F("} F{"));
  senF->Print();
  Serial.print(F("} B{"));
  senB->Print();
  Serial.println(F("}"));
  
}


float DegSensor::DisR(){
  return r;
}

float DegSensor::DisL(){
  return l;
}

float DegSensor::DisF(){
  return f;
}

float DegSensor::DisB(){
  return b;
}
