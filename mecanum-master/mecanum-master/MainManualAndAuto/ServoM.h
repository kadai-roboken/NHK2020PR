#ifndef ServoM_h
#define ServoM_h

#include <Servo.h>

class ServoM
{
  public:
  ServoM(int ServoPin,int initAngle);
  void onF();
  void onR();
  void print();
  
  private:
  Servo m_Servo;
  int m_ServoPin ;
  int m_Angle = 0;
  
};

#endif
