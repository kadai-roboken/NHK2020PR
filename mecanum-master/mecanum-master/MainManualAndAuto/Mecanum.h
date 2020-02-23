#ifndef Mecanum_h
#define Mecanum_h

#include "Motor.h"


class Mecanum
{
  public:
  Mecanum(int pin1A, int pin1B,int pin2A, int pin2B,int pin3A, int pin3B,int pin4A, int pin4B,float mode);
  void Front();
  void FRight();
  void Right();
  void BRight();
  void Back();
  void BLeft();
  void Left();
  void FLeft();
  void TurnR();
  void TurnL();
  void DriftR();
  void DriftL();
  void Rotation(float,float);
  void Go(float,float);
  void Stop();
  void Print();
  void ChangeBrake(float);
  void ChangeSpeed(float);
  void ChangeInitialVelocityCrrection(float);
  void ChangeInitialVelocity(float);
  
  private:
  int m_pin1A;
  int m_pin1B;
  int m_pin2A;
  int m_pin2B;
  int m_pin3A;
  int m_pin3B;
  int m_pin4A;
  int m_pin4B;
  float m_mode;
  int dirtheta = 90;
  Motor *motor1;
  Motor *motor2;
  Motor *motor3;
  Motor *motor4;
};

#endif
