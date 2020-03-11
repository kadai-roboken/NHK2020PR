//32,33 is broken

#include <PS3BT.h>//無線
//#include <PS3USB.h>//有線
#include <usbhub.h>
#include "PS3Con.h"
#include "Motor.h"
#include "Mecanum.h"
#include "AIR.h"
#include "ServoM.h"
#include "Right_joystick.h"//add
#define IRRCV_PIN 47

//MDはモータドライバのことね。
USB Usb;
BTD Btd(&Usb);//無線
PS3BT PS3(&Btd);//無線
//PS3USB PS3(&Usb);//有線用
PS3Con ps3con = PS3Con();
Mecanum mecanum = Mecanum(  2, 3, 4, 5, 6, 7, 44, 45, 1.3);//足場のMDに対する信号ピン。1.3はanalogWriteの値にかける比？
Right_joystick right_joystick = Right_joystick( 22, 23, 24, 25,  0.0);//最後の値0ならdigitaiWrite,1以上はanalogWrite
AIR air1 = AIR(38);
AIR air2 = AIR(39);
AIR air3 = AIR(34);
AIR air4 = AIR(35);
AIR air5 = AIR(36);
AIR air6 = AIR(37);
//Motor motor1 = Motor(42,43,0);//MDへの信号ピン。0なのでdigital
int motorr=46;
int motorl=8;

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  pinMode(IRRCV_PIN, INPUT);
  pinMode(motorr,OUTPUT);
  pinMode(motorl,OUTPUT);
  for(int i = 22; i < 32; i++){
    pinMode(i, OUTPUT);
  }   
  for(int j = 40; j < 44; j++){
    pinMode(j, OUTPUT);
  } 
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
  // フォトインタラプタの状態を確認する
  int val = digitalRead(IRRCV_PIN);
  Serial.println(val);
  
  Usb.Task();
  int angy, angx;
  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)) { //各ボタンの中にモーターを動かしたりトランジスタを動かしたりサーボを動かす処理をかいてください 
      Serial.print(F("\r\nPS"));
    }else {
    }if (PS3.getAnalogHat(RightHatX) > 240 || PS3.getAnalogHat(RightHatX) < 10) {
        //左スティック左右の値(最上部0、中央127、最下部255)を読み込む
      angx = PS3.getAnalogHat(RightHatX);    
        if (angx < 10) {
          digitalWrite(22,HIGH);
        }else{
          digitalWrite(23,HIGH);
        }       
      
    }else if (PS3.getAnalogHat(RightHatY) > 240 || PS3.getAnalogHat(RightHatY) < 10) {
        //左スティック上下の値(最上部0、中央127、最下部255)を読み込む
      angy = PS3.getAnalogHat(RightHatY);          
        if (angy < 10) {
          digitalWrite(24,HIGH);
        }else{
          digitalWrite(25,HIGH);
        }
        
    }else if (PS3.getButtonPress(TRIANGLE)) {
      Serial.print(F("\r\nTraingle"));
        analogWrite(motorr,250);
    }else if (PS3.getButtonPress(CIRCLE)) {
      Serial.print(F("\r\nCircle"));
      air5.OFA();
    }else if (PS3.getButtonPress(CROSS)) {
      Serial.print(F("\r\nCross"));
        analogWrite(motorl,250);
    }else if (PS3.getButtonPress(SQUARE)) {
      Serial.print(F("\r\nSquare"));
      air5.ONA();
    }else if (PS3.getButtonPress(UP)) {
      Serial.print(F("\r\nUp"));
      air3.OFA();
    }else  if (PS3.getButtonPress(RIGHT)) {
      Serial.print(F("\r\nRight"));
      air4.OFA();
    }else  if (PS3.getButtonPress(DOWN)) {
      Serial.print(F("\r\nDown"));
      air3.ONA();
    }else  if (PS3.getButtonPress(LEFT)) {
      Serial.print(F("\r\nLeft"));
      air4.ONA();   
    }else if (PS3.getButtonPress(L1)) {
      Serial.print(F("\r\nL1"));
      mecanum.TurnL();
      mecanum.Print();
    } else if (PS3.getButtonPress(L2)) {
      Serial.print(F("\r\nL2"));
      air1.ONA();
    }else if (PS3.getButtonPress(L3)) {
      air2.OFA();
      Serial.print(F("\r\nL3"));
    }else if (PS3.getButtonPress(R1)) {
      Serial.print(F("\r\nR1"));
      mecanum.TurnR();
      mecanum.Print();
    }else if (PS3.getButtonPress(R2)) {
      air1.OFA();
      Serial.print(F("\r\nR2"));    
    }else if (PS3.getButtonPress(R3)) {
      air2.ONA();
      Serial.print(F("\r\nR3"));
    }else if (PS3.getButtonPress(SELECT)) {
      Serial.print(F("\r\nSelect"));
      air6.OFA();
    }else if (PS3.getButtonPress(START)) {
      Serial.print(F("\r\nStart"));
      air6.ONA();
    }else if(val == 0){
      air1.OFA();
    }else {
      right_joystick.Go(ps3con.AnalogPadDistance(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY)), ps3con.AnalogPadAngle(PS3.getAnalogHat(RightHatX), PS3.getAnalogHat(RightHatY))); //motor3に使う？  
      mecanum.Go(ps3con.AnalogPadDistance(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)), ps3con.AnalogPadAngle(PS3.getAnalogHat(LeftHatX), PS3.getAnalogHat(LeftHatY)));
      mecanum.Print();
      //right_joystick.Print();
      digitalWrite(motorr,LOW);
      digitalWrite(motorl,LOW);
      digitalWrite(22,LOW);
      digitalWrite(23,LOW);
      digitalWrite(24,LOW);
      digitalWrite(25,LOW); 
                           
      Serial.println(F("\r"));
    }
  }
}

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
