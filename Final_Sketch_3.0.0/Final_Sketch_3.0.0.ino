#include <Servo.h>
//REFRENCE Pins D8-D13 all are for input operations ONLY

Servo brSer1;
Servo brSer2;

// IR Receivers
{
  const int bridgeReceiver1 = 8;
  const int bridgeReceiver2 = 9;
}

//TIME CONSTANTS
const int IRTime = 1000;//1s
const int bridgeSer = 2;// 2 millis

//previous time
{
  unsigned long prv1 = 0;
  unsigned long prv2 = 0;
  unsigned long prv3 = 0;
}

bool bridgeEnter = false;

// CONNECTION PINS
const int bridgeServoPin1 = 1;
const int bridgeServoPin2 = 2;
void setup() {
  brSer1.attach(bridgeServoPin1);
  brSer2.attach(bridgeServoPin2);
  Serial.begin(9600);
  pinMode(bridgeReceiver1, INPUT);
  pinMode(bridgeReceiver2, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

void loop() {
  build1();
  build2();
  build3();
  build4();
}

// build 1 : CONVEYOR BELT
void build1(){
}

// build 2 : BRIDGE
void build2(){
  unsigned long cT = millis();
  if((cT - prv1) > IRTime){
    prv1 = cT;
    if(digitalRead(bridgeReceiver1) == HIGH || digitalRead(bridgeReceiver2) == HIGH){
      if(bridgeEnter)
      {
      bridgeEnter = false;
      moveSer(0, brSer1);
      moveSer(0, brSer2);
      Serial.write("Ship left bridge zone");
      Serial.write("Moved both servos to " + brSer1.read());
      } else {
      bridgeEnter = true;
      moveSer(70, brSer1);
      moveSer(70, brSer2);
      Serial.write("Ship entered bridge zone");
      Serial.write("Moved both servos to " + brSer1.read());
      }
    }
  }
}

// build 3 : HARBOUR
void build3(){
}

// build 4 : ARM
void build4(){
}

void moveSer(int pos, Servo ser){
  unsigned long cT = millis();
  int pPos = ser.read();
  if((cT - prv2) > bridgeSer){
    if(pos < pPos)
      pPos--;
    else if(pos > pPos)
      pPos++;
  }
  ser.write(pos);
}