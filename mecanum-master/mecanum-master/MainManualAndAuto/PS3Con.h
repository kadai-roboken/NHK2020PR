#ifndef PS3Con_h
#define PS3Con_h

#include <PS3BT.h>
#include <usbhub.h>

class PS3Con
{
  public:
  PS3Con(); 
  int Init();
  void Start();
  void Task();
  int PS3Connected();
  int getButtonClick(int Button);
  int getButtonPress(int Button);
  double getAnalogHat(int Hat);
  float AnalogPadDistance(float x, float y);
  int AnalogPadDirection(int x, int y);
  float AnalogPadAngle(int x, int y);
  static const int AnaFront = 6;
  static const int AnaFRight = 5;
  static const int AnaRight = 4;
  static const int AnaBRight = 3;
  static const int AnaBack = 2;
  static const int AnaBLeft = 1;
  static const int AnaLeft = 8;
  static const int AnaFLeft = 7;
  static const int AnaNeutral =  0;
  static const int AnFront = 9;  
  private:
  double deg, rad;
  int AnaPadDistanceMin = 16;
  int AnaPadDistanceMax = 255;
  int pattern = 0;
  USB *Usb;
  BTD *Btd;
  PS3BT *PS3;
};

#endif
