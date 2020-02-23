#include"AIR.h"
#include"Arduino.h"

AIR::AIR(int pin){
  AIRpin = pin;
  pinMode(AIRpin,OUTPUT);

}

void AIR::ONA(){
  digitalWrite(AIRpin,HIGH);
}
void AIR::OFA(){
  digitalWrite(AIRpin,LOW);
}


