#ifndef Right_joystick_h
#define Right_joystick_h

#include "Motor.h"


class Right_joystick
{
  public:
  Right_joystick(int pin1A, int pin1B,int pin2A, int pin2B,float mode);
  
  void Front();
  void Right();
  void Back();
  void Left();
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

  float m_mode;
  int dirtheta = 90;
  Motor *joy_stick_motor1;
  Motor *joy_stick_motor2;
};

#endif
