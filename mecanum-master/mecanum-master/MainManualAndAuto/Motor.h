#ifndef Motor_h
#define Motor_h

// クラスの定義
class Motor
{
public:
  Motor(int pin1,int pin2, float mode);   // コンストラクタ
  void on(float);
  void onF();          // Led点灯
  void onR();
  void off();         // Led消灯
  void onDeg(float,float);
  float ac(float val);
  float acCorrection();
  void velocity(void);
  void ChangeStoppingCorrection(float);
  void ChangeSpeed(float);
  void ChangeInitialVelocityCrrection(float);
  void ChangeInitialVelocity(float);
  float divAc;
  float p_val;
  void print();

private:
  int m_MotorPin1;      // クラス内で使用するメンバ変数
  int m_MotorPin2;
  float m_mode;
  int F_st;
  int R_st; 
  float m_ac;
  float m_velocity;
  float m_acMax = 255;
  float m_SpeedMax = 255;
  float m_InitialVelocity = 100;
  float m_InitialVelocityCrrection = 1;
  float m_StoppingCorrection = 1;
  float m_deg = 0;
};

#endif

