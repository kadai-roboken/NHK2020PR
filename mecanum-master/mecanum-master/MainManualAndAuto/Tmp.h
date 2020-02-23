#ifndef Tmp_H
#define Tmp_H

#include <ArduinoSTL.h>


class Tmp {
  private:
  int ArgsSize = 0;
  public:
  std::vector<int> Arg;


  // コンストラクタ
  template<class... Args>
  Tmp(Args... args){
    
     tmp(args...);
  }
  
  template<class T>
  int tmp(T TMP) {
    Arg.push_back(TMP);
    ArgsSize++;
    return TMP; 
  }
  
  template<class T, class... Args>
  int tmp(T TMP, Args... args) {
    Arg.push_back(TMP);
    ArgsSize++;
    return tmp(args...);
  }

  int Size();

  
};


#endif
