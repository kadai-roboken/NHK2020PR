//#include <PS3BT.h>//無線
#include <PS3USB.h>//有線
#include <usbhub.h>
#include "PS3Con.h"
#include "Motor.h"
#include "Mecanum.h"
#include "ShagaiArm.h"
#include "GeregeArm.h"
#include "InjectionMachine.h"
#include "LineCommander.h"
#include "AIR.h"
#include "ServoM.h"
#include "Right_joystick.h"//add

//MDはモータドライバのことね。
USB Usb;
//BTD Btd(&Usb);//無線
//PS3BT PS3(&Btd);//無線
PS3USB PS3(&Usb);//有線用
PS3Con ps3con = PS3Con();
Mecanum mecanum = Mecanum(  2, 3, 4, 5, 6, 7, 44, 45, 1.3);//足場のMDに対する信号ピン。1.3はanalogWriteの値にかける比？
Right_joystick right_joystick = Right_joystick( 22, 23, 24, 25,  0.0);//最後の値0ならdigitaiWrite,1以上はanalogWrite
//ShagaiArm armS = ShagaiArm(31, 32, 33, 0);
//ShagaiArm armS = ShagaiArm(49, 22, 24, 0);
//GeregeArm armG = GeregeArm(36, 37, 38, 39, 0);
//InjectionMachine IM = InjectionMachine(40, 41, 0);
LineCommander sen = LineCommander(200,10, 0, 0, 0);
AIR air1 = AIR(32);
AIR air2 = AIR(33);
AIR air3 = AIR(34);
AIR air4 = AIR(35);
AIR air5 = AIR(36);
AIR air6 = AIR(37);
//Motor motor1 = Motor(42,43,0);//MDへの信号ピン。0なのでdigital
int motorr=46;
int motorl=9;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));



//  sen.SetL_D(29, 30, 31);
//  sen.SetR_D(27, 26, 25);
//  sen.SetF_A(A8, A9);
//  sen.SetB_A(A10, A11);
  pinMode(motorr,OUTPUT);
  pinMode(motorl,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT); 
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);  
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT); 
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT); 
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT); 
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);         
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);  

}
void loop() {
  digitalWrite(26,HIGH);
  digitalWrite(27,HIGH);  
  digitalWrite(28,HIGH);
  digitalWrite(29,HIGH);  
  digitalWrite(30,HIGH);
  digitalWrite(31,HIGH);  
  digitalWrite(40,HIGH);
  digitalWrite(41,HIGH);  
  digitalWrite(42,HIGH);
  digitalWrite(43,HIGH);

  Usb.Task();
  int angy, angx;
  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)) { //各ボタンの中にモーターを動かしたりトランジスタを動かしたりサーボを動かす処理をかいてください
      //air5.ONA(); 
      Serial.print(F("\r\nPS"));
    }
    else {
    }if (PS3.getAnalogHat(RightHatX) > 200 || PS3.getAnalogHat(RightHatX) < 50) {
        //左スティック上下の値(最上部0、中央127、最下部255)を読み込む
      angx = PS3.getAnalogHat(RightHatX);    

     if (angx < 50) {
      digitalWrite(22,HIGH);
     }else{
      digitalWrite(23,HIGH);
     }       
      
    }else if (PS3.getAnalogHat(RightHatY) > 200 || PS3.getAnalogHat(RightHatY) < 50) {
        //左スティック上下の値(最上部0、中央127、最下部255)を読み込む
      angy = PS3.getAnalogHat(RightHatY);     
      
     if (angy < 50) {
      digitalWrite(24,HIGH);
     }else{
      digitalWrite(25,HIGH);
     }
    }else if (PS3.getButtonPress(TRIANGLE)) {
      Serial.print(F("\r\nTraingle"));
//      armG.Bend();
//      motor1.onF();//Fだから正転
        analogWrite(motorr,250);

    }
    else if (PS3.getButtonPress(CIRCLE)) {
      Serial.print(F("\r\nCircle"));
    //  armS.Grab();
      air5.OFA();
    }
    else if (PS3.getButtonPress(CROSS)) {
      Serial.print(F("\r\nCross"));
//      armG.Stretch();
//      motor1.onR();//Rだから逆転
        analogWrite(motorl,250);
     
    }
    else if (PS3.getButtonPress(SQUARE)) {
      Serial.print(F("\r\nSquare"));
      //armS.Release();
      air5.ONA();
    }
    else if (PS3.getButtonPress(UP)) {
      Serial.print(F("\r\nUp"));
      //armS.Stretch();
      air3.OFA();
    }
    else  if (PS3.getButtonPress(RIGHT)) {
      Serial.print(F("\r\nRight"));
      air4.OFA();
    }
    else  if (PS3.getButtonPress(DOWN)) {
      Serial.print(F("\r\nDown"));
      //armS.Bend();
      air3.ONA();
    }
    else  if (PS3.getButtonPress(LEFT)) {
      Serial.print(F("\r\nLeft"));
      air4.ONA();   
    }
    else if (PS3.getButtonPress(L1)) {
      Serial.print(F("\r\nL1"));
      mecanum.TurnL();
      mecanum.Print();
    } else if (PS3.getButtonPress(L2)) {
      Serial.print(F("\r\nL2"));
      air6.ONA();
//      Serial.print(F("auto:"));
//      Serial.print(F("deg "));
//      Serial.print(sen.Angle(), 4);
//      Serial.print(F("    distans "));
//      Serial.print(sen.Distance(), 4);
//      Serial.print(F("  "));
//      mecanum.Rotation(225,sen.Rotate()+9);
//      if(sen.Angle() > -15 && sen.Angle() < 15){
//        mecanum.Front();
//      }else{
//        
//        mecanum.Go(100*sen.Distance(),sen.Angle()+90);
//      }
//      mecanum.Print();
//      Serial.println();
    }else if (PS3.getButtonPress(L3)) {
      air2.OFA();
      Serial.print(F("\r\nL3"));
    }
    else if (PS3.getButtonPress(R1)) {
      Serial.print(F("\r\nR1"));
      mecanum.TurnR();
      mecanum.Print();
    }
    else if (PS3.getButtonPress(R2)) {
      Serial.print(F("\r\nR2"));
      air6.OFA();
//      Serial.print(F("auto:"));
//      Serial.print(F("deg "));
//      Serial.print(sen.Angle(), 4);
//      Serial.print(F("    distans "));
//      Serial.print(sen.Distance(), 4);
//      Serial.print(F("  "));
//      mecanum.Print();
//      Serial.println();     
    }
    else if (PS3.getButtonPress(R3)) {
      air2.ONA();
      Serial.print(F("\r\nR3"));
    }
    else if (PS3.getButtonPress(SELECT)) {
      Serial.print(F("\r\nSelect"));
      air1.OFA();
    }
    else if (PS3.getButtonPress(START)) {
      Serial.print(F("\r\nStart"));
//      IM.Inject();
      air1.ONA();
    }
    else {
       //my_left_analog_pad(ps3con.AnalogPadDirection(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
      //motor1.off();
      //right_joystick.Go(ps3con.AnalogPadDistance(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY)), ps3con.AnalogPadAngle(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY))); //motor3に使う？  
      mecanum.Go(ps3con.AnalogPadDistance(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)), ps3con.AnalogPadAngle(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
      mecanum.Print();
      //right_joystick.Print();
      digitalWrite(motorr,LOW);
      digitalWrite(motorl,LOW);
      digitalWrite(22,LOW);
      digitalWrite(23,LOW);
      digitalWrite(24,LOW);
      digitalWrite(25,LOW); 
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(44,LOW);
      digitalWrite(45,LOW);                           
      Serial.println(F("\r"));
    }
  }
}

////以下メカナムの関数
//void my_left_analog_pad{
//    if(ps3con.AnaFront){
//      Serial.print(F("\r\nfront"));
//      mecanum.Front();
//    }else if( ps3con.AnaFRight){
//      Serial.print(F("\r\nfront_right"));
//      mecanum.FRight();
//    }else if( ps3con.AnaRight){
//      Serial.print(F("\r\nright"));
//      mecanum.Right();
//    }else if(ps3con.AnaBRight){
//      Serial.print(F("\r\nback_right"));
//      mecanum.BRight();
//    }else if (ps3con.AnaBack){
//      Serial.print(F("\r\nback"));
//      mecanum.Back();
//    }else if(ps3con.AnaBLeft){
//      Serial.print(F("\r\nback_left"));
//      mecanum.BLeft();
//    }else if (ps3con.AnaLeft){
//      Serial.print(F("\r\nleft"));
//      mecanum.Left();
//    }else if ps3con.AnaFLeft){
//      Serial.print(F("\r\nfront_left"));
//      mecanum.FLeft();
//    }else{
//      Serial.print(F("\r\nstop"));
//      mecanum.Stop();
//      //Serial.print(F("\r\nstop1"));
//  }
//}

//以下メカナムの関数
void my_left_analog_pad(int n) {
  switch (n) {
    case ps3con.AnaFront:
      Serial.print(F("\r\nfront"));
      mecanum.Front();
      break;
    case ps3con.AnaFRight:
      Serial.print(F("\r\nfront_right"));
      mecanum.FRight();
      break;
    case ps3con.AnaRight:
      Serial.print(F("\r\nright"));
      mecanum.Right();
      break;
    case ps3con.AnaBRight:
      Serial.print(F("\r\nback_right"));
      mecanum.BRight();
      break;
    case ps3con.AnaBack:
      Serial.print(F("\r\nback"));
      mecanum.Back();
      break;
    case ps3con.AnaBLeft:
      Serial.print(F("\r\nback_left"));
      mecanum.BLeft();
      break;
    case ps3con.AnaLeft:
      Serial.print(F("\r\nleft"));
      mecanum.Left();
      break;
    case ps3con.AnaFLeft:
      Serial.print(F("\r\nfront_left"));
      mecanum.FLeft();
      break;
    case ps3con.AnaNeutral:
      Serial.print(F("\r\nstop"));
      mecanum.Stop();
      break;
    default:
      Serial.print(F("\r\nstop1"));
  }
}
//ここまで
//ここからは右ジョイスティックで
//void my_right_analog_pad(int n) {
//  switch (n) {
//    case ps3con.AnaFront:
//      Serial.print(F("\r\nfront"));
//      //right_joystick.Front(); //前に倒すとモータ２が正転 
//      digitalWrite(22,HIGH);  
//      digitalWrite(23,LOW);
//      digitalWrite(24,LOW);
//      digitalWrite(25,LOW);          
//      break;
//    case ps3con.AnaRight:
//      Serial.print(F("\r\nright"));
//      //right_joystick.Right();//右に倒すとモータ３が正転   
//      digitalWrite(22,LOW);  
//      digitalWrite(23,HIGH);
//      digitalWrite(24,LOW);
//      digitalWrite(25,LOW);         
//      break;
//    case ps3con.AnaBack:
//      Serial.print(F("\r\nback"));
//      //right_joystick.Back();//後ろに倒すとモータ２が逆転
//      digitalWrite(22,LOW);  
//      digitalWrite(23,LOW);
//      digitalWrite(24,HIGH);
//      digitalWrite(25,LOW);            
//      break;
//    case ps3con.AnaLeft:
//      Serial.print(F("\r\nleft"));
//      right_joystick.Left();//左に倒すとモータ３が逆転
//      digitalWrite(22,LOW);  
//      digitalWrite(23,LOW);
//      digitalWrite(24,LOW);
//      digitalWrite(25,HIGH);          
//      break;
//    case ps3con.AnaNeutral:
//      Serial.print(F("\r\nstop"));
//      right_joystick.Stop();//何もしないとき
//      break;
//    default:
//      Serial.print(F("\r\nstop1"));
//  }
//}
