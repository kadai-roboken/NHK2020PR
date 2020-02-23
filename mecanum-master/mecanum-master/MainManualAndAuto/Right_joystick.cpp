#include "Arduino.h"
#include "Right_joystick.h"

Right_joystick::Right_joystick(int pin1A, int pin1B,int pin2A, int pin2B, float mode)
{
  m_pin1A=pin1A;
  m_pin1B=pin1B;
  m_pin2A=pin2A;
  m_pin2B=pin2B;
  m_mode=mode;
  joy_stick_motor1 = new Motor(m_pin1A,m_pin1B,m_mode);
  joy_stick_motor2 = new Motor(m_pin2A,m_pin2B,m_mode);
  ChangeBrake(1.5);
  ChangeSpeed(200);
  ChangeInitialVelocityCrrection(1.5);
  ChangeInitialVelocity(100);
}

void Right_joystick::Front(){
  joy_stick_motor1->onF();//F
  joy_stick_motor2->off();

}

void Right_joystick::Right(){
  joy_stick_motor1->off();
  joy_stick_motor2->onF();//F

}

void Right_joystick::Back(){
  joy_stick_motor1->onR();//R
  joy_stick_motor2->off(); 
}

void Right_joystick::Left(){
  joy_stick_motor1->off();
  joy_stick_motor2->onR();  //R
}
void Right_joystick::Go(float power, float deg){
  joy_stick_motor1->onDeg(power,deg+45 - dirtheta);
  joy_stick_motor2->onDeg(power,deg-45 - dirtheta+180);
  if(power == 0){
    joy_stick_motor1->off();
    joy_stick_motor2->off();
  }
}

void Right_joystick::Rotation(float power,float deg){
  joy_stick_motor1->onDeg(power,deg/2 - dirtheta-90);
  joy_stick_motor2->onDeg(power,deg/2 - dirtheta-90);
  if(power == 0){
    joy_stick_motor1->off();
    joy_stick_motor2->off();
  }
}

void Right_joystick::Stop(){
  joy_stick_motor1->off();
  joy_stick_motor2->off();
}

void Right_joystick::ChangeBrake(float correction){
  joy_stick_motor1->ChangeStoppingCorrection(correction);
  joy_stick_motor2->ChangeStoppingCorrection(correction);
}

void Right_joystick::ChangeSpeed(float SpeedMax){
  joy_stick_motor1->ChangeSpeed(SpeedMax);
  joy_stick_motor2->ChangeSpeed(SpeedMax);
}

void Right_joystick::ChangeInitialVelocityCrrection(float InitialVelocityCrrection){
  joy_stick_motor1->ChangeInitialVelocityCrrection(InitialVelocityCrrection);
  joy_stick_motor2->ChangeInitialVelocityCrrection(InitialVelocityCrrection);  
}

void Right_joystick::ChangeInitialVelocity(float InitialVelocity){
  joy_stick_motor1->ChangeInitialVelocity(InitialVelocity);
  joy_stick_motor2->ChangeInitialVelocity(InitialVelocity);
}

void Right_joystick::Print(){
  joy_stick_motor1->print();
  joy_stick_motor2->print();
}
