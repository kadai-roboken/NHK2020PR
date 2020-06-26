#include <SoftwareSerial.h>
#include "AIR.h"
#include "Motor.h"
#include "math.h"

#define MYRX 12 //デジタル12番ピンはソフトウェアシリアルRX
#define MYTX 11 //デジタル11番ピンはソフトウェアシリアルTX
SoftwareSerial mySerial(MYRX, MYTX);
//0,1はシリアル通信に使っているから使わないで。
//旋回はゆっくり？
//ジョイスティック、各軸、11段階ぐらいに分けるぐらいがちょうどいい？

unsigned char c[8];
unsigned long chksum;
  
const int TRFf = PC8;//3/3,
const int TRFb = PA11;//1/4
const int TRBf = 2;//1/3
const int TRBb = 3;//2/2
const int TLFf = 4;//3/2
const int TLFb = 5;//3/1
const int TLBf = 7;//1/1
const int TLBb = 8;//1/2
const int Pf = PB6;//4/1
const int Pb = PA5;//2/1
const int Hf = PB9;//4/3
const int Hb = PB8;//4/4
const int Lf = PB15;//1/3N
const int Lb = PB14;//1/2N

AIR air1 = AIR(PA13);
AIR air2 = AIR(PA14);
AIR air3 = AIR(PC14);
AIR air4 = AIR(PC15);
AIR air5 = AIR(PH0);
AIR air6 = AIR(PH1);

void setup() {
  mySerial.begin(2400);//SBDBTとArduinoは2400bps
  Serial.begin(19200);//シリアルモニター表示
  c[0] = 0x80; //SBDBTからのシリアル信号の１個目は固定。
  
  pinMode(TRFf,OUTPUT);//3/3,
  pinMode(TRFb,OUTPUT);//1/4,3/4,2/4
  pinMode(TRBf,OUTPUT);//1/3
  pinMode(TRBb,OUTPUT);//2/2,
  pinMode(TLFf,OUTPUT);//3/2
  pinMode(TLFb,OUTPUT);//3/1
  pinMode(TLBf,OUTPUT);//1/1
  pinMode(TLBb,OUTPUT);//1/2
}

void motor(int Lup,int x,int y, double theta ){
  if(theta>=70.0 && theta<=110.0){//front
    analogWrite(TRBf, y);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, y);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, y);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, y);
    analogWrite(TLBb, 0);
  }
  else if(theta>=-110.0 && theta<=-70.0){//back
    analogWrite(TRBf, 0);
    analogWrite(TRBb, -y);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, -y);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, -y);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, -y);
  }
  else if(theta>=-20.0 && theta<=20.0){//right
    analogWrite(TRBf, x);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, x);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, x);
    analogWrite(TLBf, x);
    analogWrite(TLBb, 0);
  }
  else if(theta>=160.0 && theta<180.1){//left
    analogWrite(TRBf, 0);
    analogWrite(TRBb, -x);
    analogWrite(TLFf, -x);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, -x);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, -x);
  }
  else if(theta>-180.1 && theta<=-160.0){//left
    analogWrite(TRBf, 0);
    analogWrite(TRBb, -x);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, -x);
    analogWrite(TRFf, -x);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, -x);
    analogWrite(TLBb, 0);
  }  
  else if(theta>20.0 && theta<70.0){//rfront
    analogWrite(TRBf, Lup);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, Lup);
    analogWrite(TLBb, 0);
  }
  else if(theta>110.0 && theta<=135.0){//lfront
    analogWrite(TRBf, 0);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, Lup);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, Lup);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, 0);
  }
  else if(theta>135.0 && theta<160.0){//lfront
    analogWrite(TRBf, 0);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, -Lup);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, -Lup);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, 0);
  }
  else if(theta>=-45.0 && theta<-20.0){//rback
    analogWrite(TRBf, 0);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, Lup);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, Lup);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, 0);
  }
  else if(theta>-70.0 && theta<-45.0){//rback
    analogWrite(TRBf, 0);
    analogWrite(TRBb, 0);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, -Lup);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, -Lup);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, 0);
  }
  else if(theta>-160.0 && theta<-110.0){//lback
    analogWrite(TRBf, 0);
    analogWrite(TRBb, -Lup);
    analogWrite(TLFf, 0);
    analogWrite(TLFb, 0);
    analogWrite(TRFf, 0);
    analogWrite(TRFb, 0);
    analogWrite(TLBf, 0);
    analogWrite(TLBb, -Lup);
  }        
  else{
//    analogWrite(TRBf, 0);
//    analogWrite(TRBb, 0);
//    analogWrite(TLFf, 0);
//    analogWrite(TLFb, 0);
//    analogWrite(TRFf, 0);
//    analogWrite(TRFb, 0);
//    analogWrite(TLBf, 0);
//    analogWrite(TLBb, 0);
  }
}

void loop() {
  //まずは無線からシリアルを読み込む。c[1]とc[2]にキー入力が格納される。
  double Lup; 
  int i;
  if (mySerial.available() >= 8) { //8byte以上あるかチェック
    if (mySerial.read() == 0x80) { //１byte読み込んで0x80のスタートビットかチェック
      Serial.print(c[0], HEX); //１６進数で数値を表示。
      Serial.print(",");//コンマで区切る。
      for (chksum = c[0], i = 1; i < 8; i++) { //スタートビットは読み込み済みなので、次の７個のデータを読み込む。
        c[i] = mySerial.read();
        if (i < 7) chksum += c[i];
        Serial.print(c[i], HEX); //１６進数で数値を表示。
        Serial.print(",");//}//コンマで区切る。
      }
      if (c[7] == (chksum & 0x7F)) { //ボタン部分のみのチェックサムを簡易計算してみる。
        Serial.println("check sum OK !");//チェックサムOKを表示。
      }
      else {
        Serial.println("check sum * * ERROR * *");//ダメならエラーを表示。
      }
      
      //アナログハットの部分
      String leftstickx =  String(c[3], DEC); //左のアナログスティックライトの左右の値を16→10進数へ
      String leftsticky =  String(c[4], DEC); //左のアナログスティックライトの上下の値を16→10進数へ
      String rightstickx =  String(c[5], DEC); //右のアナログスティックライトの左右の値を16→10進数へ
      String rightsticky =  String(c[6], DEC); //右のアナログスティックライトの上下の値を16→10進数へ
//      Serial.print(leftstickx);
//      Serial.print(leftsticky);
//      Serial.print(rightstickx);
//      Serial.println(rightsticky);
       Serial.print("\t");
      
      int Leftstickx = leftstickx.toInt();
      int Leftsticky = leftsticky.toInt(); 
      int x = (Leftstickx - 64)*4;
      int y1 = (Leftsticky - 64)*4;
      int y = -1*y1;
      float a = atan2(y, x);
      float theta = a / 3.14159 * 180;
      Lup = sqrt(pow(x,2)+pow(y,2))*0.75;
      //Rup = (0 - x - y);
      Serial.print("  Lup=");
      Serial.print(  Lup);
      Serial.print(" x=");
      Serial.print(x);
      Serial.print(" y=");      
      Serial.print(y);
      Serial.print(" theta=");
      Serial.print(theta);
      Serial.print("°");
      
      //ここから、キー入力に応じて、メッセージを出す。
      if (c[1] == 0x00 ) { //何も押されていなければ静止
        if (c[2] == 0x00 ) { //何も押されていなければ静止
//          analogWrite(TRFf,0);//1/2
//          analogWrite(TRFb,0);//1/3
//          analogWrite(TRBf,0);//1/3N
//          analogWrite(TRBb,0);//1/1
//          analogWrite(TLFf,0);//1/4
//          analogWrite(TLFb,0);//15/1
//          analogWrite(TLBf,0);//15/2
//          analogWrite(TLBb,0);//3/2 
          Serial.println("* STOP *");
        }
      }
      
      if ((c[2] & 0x01) == 0x01 && (c[2] & 0x02) == 0x02) {
        //if ((c[2] & 0x03 ) == 0x03 ) { //Start(上下同時押しはないと言う前提で書いてるので、注意！）
        air6.ONA();   
        Serial.println("Start");

      } else  if ((c[2] & 0x04) == 0x04 && (c[2] & 0x08) == 0x08) {//左右同時押しはないと言う前提で書いてるので、注意！）
        // if ((c[2] & 0x0C ) == 0x0C ) { //Select
        air6.OFA();
        Serial.println("Select");

      } else {


        if ((c[2] & 0x01) == 0x01 ) { //上
          Serial.println("↑Up");    
        }
        else if ((c[2] & 0x02) == 0x02 ) { //下 
          Serial.println("↓Down");
        }
        else if ((c[2] & 0x03 ) == 0x03 ) { //Start
          Serial.println("Start");
        }
        else if ((c[2] & 0x05 ) == 0x05 ) { //Start
          Serial.println("PS");
        }
        else if ((c[2] & 0x04 ) == 0x04 ) { //右
          Serial.println("→Right");
        }
        else if ((c[2] & 0x08 ) == 0x08 ) { //左
          Serial.println("←Left");
        }
        else if ((c[2] & 0x10 ) == 0x10 ) { //三角
          Serial.println("Triangle△");
        }
        else if ((c[2] & 0x20 ) == 0x20 ) { //バツ
          Serial.println("×Cross");
        }
        else if ((c[2] & 0x40 ) == 0x40 ) { //マル
          air5.ONA();//アーム掴む
          Serial.println("○Circle");
        }
        else if ((c[1] & 0x01 ) == 0x01 ) { //四角
          air5.ONA();//アーム掴む
          delay(500);       
          air4.OFA();//pass 
          delay(295);
          air5.OFA();//アーム離す
          Serial.println("□Square");
        }
        else if ((c[1] & 0x02 ) == 0x02 ) { //L1 turn light
          analogWrite(TRBf, 100);
          analogWrite(TRBb, 0);
          analogWrite(TLFf, 100);
          analogWrite(TLFb, 0);
          analogWrite(TRFf, 0);
          analogWrite(TRFb, 100);
          analogWrite(TLBf, 0);
          analogWrite(TLBb, 100);                    
          Serial.println("L1");
        }
        else if ((c[1] & 0x04 ) == 0x04 ) { //L2
          air2.ONA();
          Serial.println("L2");
        }
        else if ((c[1] & 0x20 ) == 0x20 ) { //L3
          Serial.println("L3");
        }
        else if ((c[1] & 0x08 ) == 0x08 ) { //R1 turn right
          analogWrite(TRBf, 0);
          analogWrite(TRBb, 100);
          analogWrite(TLFf, 0);
          analogWrite(TLFb, 100);
          analogWrite(TRFf, 100);
          analogWrite(TRFb, 0);
          analogWrite(TLBf, 100);
          analogWrite(TLBb, 0);
          Serial.println("R1");
        }
        else if ((c[1] & 0x10 ) == 0x10 ) { //R2
          Serial.println("R2");
        }
        else if ((c[1] & 0x40 ) == 0x40 ) { //R3
          air3.ONA();//エアシリンダーをギアに押し当てる         
          Serial.println("R3");
        }
        else if ((c[1] & 0x80 ) == 0x80 ) { //PS
          Serial.println("PS");
        }else{
          motor(Lup,x,y, theta);
       }
      }
    }
  }
}