#include "Arduino.h"
#include "Motor.h"


// コンストラクタ（初期化処理）
Motor::Motor(int pin1, int pin2, float mode)
{
  m_MotorPin1 = pin1;             // メンバ変数にピン番号を代入
  m_MotorPin2 = pin2;
  m_mode = mode;
  F_st = 0;
  R_st = 0; 
  m_ac = 0;
  divAc = m_mode;
  pinMode(m_MotorPin1, OUTPUT);  // ピンモードを指定
  pinMode(m_MotorPin2, OUTPUT);
}

void Motor::on(float power){
  if(m_mode == 0)
  {
    if(power > 0){
      F_st = 1;
      R_st = 0;
      digitalWrite(m_MotorPin1, HIGH);
      digitalWrite(m_MotorPin2, LOW);
    }else if(power <0){
      F_st = 0;
      R_st = 1;
      digitalWrite(m_MotorPin1, LOW);
      digitalWrite(m_MotorPin2, HIGH);
    }else{
      F_st = 0;
      R_st = 0;
      digitalWrite(m_MotorPin1, LOW);
      digitalWrite(m_MotorPin2, LOW);
      
    }
  }
  else
  {
    if(power > 0){
      analogWrite(m_MotorPin1, power);
      analogWrite(m_MotorPin2, LOW); 
    }else if(power < 0){
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, -m_velocity); 
    }else{
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, LOW);
    }
  }
}

void Motor::onF(void)
{
  if(m_mode == 0)
  {
    F_st = 1;
    R_st = 0;
    digitalWrite(m_MotorPin1, HIGH);
    digitalWrite(m_MotorPin2, LOW);
  }
  else
  {
    ac(divAc);
    velocity();
    if(m_velocity > 0){
      analogWrite(m_MotorPin1, m_velocity);
      analogWrite(m_MotorPin2, LOW); 
    }else if(m_velocity < 0){
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, -m_velocity); 
    }else{
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, LOW);
    }
  }
}

void Motor::onR(void)
{
  if(m_mode == 0)
  {
    F_st = 0;
    R_st = 1;
    digitalWrite(m_MotorPin1, LOW);
    digitalWrite(m_MotorPin2, HIGH);
  }
  else
  {
    ac(-divAc);
    velocity();
    if(m_velocity > 0){
      analogWrite(m_MotorPin1, m_velocity);
      analogWrite(m_MotorPin2, LOW); 
    }else if(m_velocity < 0){
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, -m_velocity); 
    }else{
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, LOW);
    }
  }
}


void Motor::off(void)
{
  if(m_mode == 0)
  {
    F_st = 0;
    R_st = 0;
    digitalWrite(m_MotorPin1, LOW);
    digitalWrite(m_MotorPin2, LOW);
  }
  else
  {
    ac(0);
    velocity();
    if(m_ac > 0){
      analogWrite(m_MotorPin1, m_ac);
      analogWrite(m_MotorPin2, LOW);
      }else if(m_ac < 0){
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, -m_ac);
      }else{
      analogWrite(m_MotorPin1, LOW);
      analogWrite(m_MotorPin2, LOW);
      }
  }
}

void Motor::onDeg(float power, float deg){
  m_velocity = power*sin(2*PI*deg/360);
  on(m_velocity);
}

float Motor::acCorrection(){
  float acCor;
  if(m_ac > 0){
    acCor = sin(PI/2*m_ac/m_acMax);
  }else if(m_ac < 0){
    acCor = sin(PI/2*(-m_ac)/m_acMax);
  }else{
    acCor = 0;
  }
  return acCor;
}

float Motor::ac(float val){
  if(val > 0)
  {
    if(m_ac < m_InitialVelocity){
      val = val * m_InitialVelocityCrrection;
    }else{
      
    }
    
    m_ac += val;
    if (m_ac > m_SpeedMax)
    {
      m_ac =m_SpeedMax;
    }
  }
  else if(val < 0)
  {
    if(m_ac > -m_InitialVelocity){
      val = val * m_InitialVelocityCrrection;
    }else{
      
    }
    m_ac += val;
    if(m_ac < -m_SpeedMax)
    {
      m_ac = -m_SpeedMax;
    }
  }
  else
  {
    if(m_ac > divAc)
    {
      m_ac -= divAc*m_StoppingCorrection;
    }
    else if(m_ac < -divAc)
    {
      m_ac += divAc*m_StoppingCorrection;
    }
    else
    {
      m_ac = 0;
    }
  }
}

void Motor::velocity(){
    m_velocity = m_ac*acCorrection();
}


void Motor::ChangeStoppingCorrection(float StoppingCorrection){
  m_StoppingCorrection = StoppingCorrection;
}

void Motor::ChangeSpeed(float SpeedMax){
  m_SpeedMax = SpeedMax;
}

void Motor::ChangeInitialVelocityCrrection(float InitialVelocityCrrection){
  m_InitialVelocityCrrection = InitialVelocityCrrection;
}


void Motor::ChangeInitialVelocity(float InitialVelocity){
  m_InitialVelocity = InitialVelocity;
}

void Motor::print(void)
{
  if(m_mode == 0)
  {
    Serial.print(F("F_st:["));
    Serial.print(F_st);
    Serial.print(F("]"));
    Serial.print(F("R_st:["));
    Serial.print(R_st);
    Serial.print(F("]"));
  }else{
//    p_val = m_ac;
    p_val = m_velocity;
    Serial.print(F("velocity:["));
    Serial.print(p_val,4);
    Serial.print(F("] "));
  }
}
