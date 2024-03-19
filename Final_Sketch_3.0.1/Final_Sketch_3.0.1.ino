#include <Servo.h>
//REFRENCE Pins D8-D13 all are for input operations ONLY

Servo brSer1;
Servo brSer2;
Servo armSerA;//arm :: to lift the arm
Servo armSerB;//arm :: to rotate the base

// IR Receivers
const int bridgeReceiver1 = 8;
const int bridgeReceiver2 = 9;
const int armShipDe = 10;

//relays
const int armMag = 5;

//TIME CONSTANTS
const int IRTime = 1000;//1s
const int SerTime = 2;// 2 millis

//arm movement constants
const int base = 180;
const int arm = 90;

//previous time
unsigned long prv1 = 0;
unsigned long prv2 = 0;
unsigned long prv3 = 0;
unsigned long prv4 = 0;
unsigned long prv5 = 0;

bool bridgeEnter = false;

// CONNECTION PINS
const int bridgeServoPin1 = 1;
const int bridgeServoPin2 = 2;
const int armServoPinArm = 3;
const int armServoPinBase = 4;

void setup() {
  brSer1.attach(bridgeServoPin1);
  brSer2.attach(bridgeServoPin2);
  armSerA.attach(armServoPinArm);
  armSerB.attach(armServoPinBase);
  
  Serial.begin(9600);
  
  pinMode(bridgeReceiver1, INPUT);
  pinMode(bridgeReceiver2, INPUT);
  pinMode(armShipDe, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  
  pinMode(armMag, OUTPUT);
  brSer1.write(0);
  brSer2.write(0);
  armSerA.write(0);
  armSerB.write(0);
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
      Serial.println("Bridge :: Ship left bridge zone\n");
      Serial.println("Bridge :: Moved both servos to " + brSer1.read());
      } else {
      bridgeEnter = true;
      moveSer(70, brSer1);
      moveSer(70, brSer2);
      Serial.println("Bridge :: Ship entered bridge zone\n");
      Serial.println("Bridge :: Moved both servos to " + brSer1.read());
      }
    }
  }
}

// build 3 : HARBOUR
void build3(){
  
}

// build 4 : ARM
void build4(){
  unsigned long cTM = millis();
  if((cTM - prv4) > 5000){
    prv4 = cTM;
    if(digitalRead(armShipDe) == HIGH){

      digitalWrite(armMag, HIGH);
      Serial.println("Arm :: Magnet activated");
      moveSer(0, armSerB);
      moveSer(0, armSerA);
      Serial.print("Arm :: Arms set to postion :" + armSerB.read());
      Serial.println(" " + armSerA.read());
        
      unsigned long cT = millis();
      if((cT - prv5) > 500){
        digitalWrite(armMag, HIGH);
        Serial.println("Arm :: Magnet de-activated");
        moveSer(base, armSerB);
        moveSer(arm, armSerA);
        Serial.print("Arm :: Arms set to postion :" + armSerB.read());
        Serial.println(" " + armSerA.read());
      }
    }
  }
}

//to move any servo to the given degrees
void moveSer(int pos, Servo ser){
  unsigned long cT = millis();
  int pPos = ser.read();
  if((cT - prv2) > SerTime){
    if(pos < pPos)
      pPos--;
    else if(pos > pPos)
      pPos++;
  }
  ser.write(pos);
}