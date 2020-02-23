#include "ServoM.h"
#include "Arduino.h"

ServoM::ServoM(int ServoPin,int initAngle){
  m_ServoPin = ServoPin;
  m_Angle = initAngle;
  
}



void ServoM::onF()
{
  m_Servo.attach(m_ServoPin);
  m_Angle++;
  if(m_Angle >= 180){
    m_Angle = 180;
  }else if(m_Angle <= 0){
    m_Angle = 0;
  }
  m_Servo.write(m_Angle);
  
}

void ServoM::onR()
{
  m_Servo.attach(m_ServoPin);
  m_Angle--;
  if(m_Angle >= 180){
    m_Angle = 180;
  }else if(m_Angle <= 0){
    m_Angle = 0;
  }
  m_Servo.write(m_Angle);
}

void ServoM::print(){
  Serial.print(F("Angle:["));
  Serial.print(m_Angle);
  Serial.print(F("]"));
}

