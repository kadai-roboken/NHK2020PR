#ifndef DegSensor_H
#define DegSensor_H
#include "Sensors.h"

class DegSensor{
  
  public:
  DegSensor(){
  }
  
  template<class...Args>
  void SetR_D(Args...args){
    senR = new Sensors(args...);
    R_DA = 0;
  }
  template<class...Args>
  void SetR_A(Args...args){
    senR = new Sensors(args...);
    R_DA = 1;
  }
  
  template<class...Args>
  void SetL_D(Args...args){
    senL = new Sensors(args...);
    L_DA = 0;
  }
  template<class...Args>
  void SetL_A(Args...args){
    senL = new Sensors(args...);
    L_DA = 1;
  }
  
  template<class...Args>
  void SetF_D(Args...args){
    senF = new Sensors(args...);
    F_DA = 0;
  }
  template<class...Args>
  void SetF_A(Args...args){
    senF = new Sensors(args...);
    F_DA = 1;
  }
  
  template<class...Args>
  void SetB_D(Args...args){
    senB = new Sensors(args...);
    B_DA = 0;
  }
  template<class...Args>
  void SetB_A(Args...args){
    senB = new Sensors(args...);
    B_DA = 1;
  }
  void Trace(int);
  float TraceAng(int);
  float TraceDis(int);
  float DisR();
  float DisL();
  float DisF();
  float DisB();
  void Print();

  private:
  Sensors *senR,*senL,*senF,*senB;
  float r,l,f,b;
  int L_DA,R_DA,F_DA,B_DA;
};



#endif
