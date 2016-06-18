/* Babybot code for intercampus technical team
 * 
 *The following code is run on Arduino nano
 *The code function is to obtain data from serial communication via Bluetooth
 *and interpret the data to control 2 DC motor and a Servo
 *The Arduino is connected to L293D for motor driving
 *
 */

#include <Servo.h>

//--------Declare objects
Servo srv;
int enl = 11;
int enr = 12;
int lMPin1 = 6;          
int lMPin2 = 7;         
int rMPin1 = 9;         
int rMPin2 = 10; 
int Rstate, Lstate = 0;
String readString;

//-------------Setup Void
void setup() {
  Serial.begin(9600);
  srv.attach(5);
  pinMode(lMPin1, OUTPUT);
  pinMode(lMPin2, OUTPUT);
  pinMode(rMPin1, OUTPUT);
  pinMode(rMPin2, OUTPUT);
  pinMode(enl, OUTPUT);
  pinMode(enr, OUTPUT);
  digitalWrite(enl,Lstate);
  digitalWrite(enr,Rstate);
}

//-----------Loop Void
void loop() {
  digitalWrite(enl,Lstate);
  digitalWrite(enr,Rstate);
  //--------------------------Read Serial
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  //---------------------------Execute Command
  if (readString.length() >0) {
    Serial.println(readString);
     if(readString == "Aon" && Rstate == 0 && Lstate == 0){
      Rstate = 1;
      Lstate = 1;
      Serial.println("Motor Armed");
     }else if(readString == "Aof" && Rstate == 1 && Lstate == 1){
      Rstate = 0;
      Lstate = 0;      
      Serial.println("Motor Disarmed");
    }else if(readString == "lon"){
      digitalWrite(lMPin1,0);
      digitalWrite(rMPin1,1);
      Serial.println("Left");
    }else if(readString == "ron"){
      digitalWrite(lMPin1,1);
      digitalWrite(rMPin1,0);
       Serial.println("Right");
    }else if(readString == "fon"){
      digitalWrite(lMPin1,1);
      digitalWrite(rMPin1,1);
      Serial.println("Forward");
    }else if(readString == "lof"){
      digitalWrite(rMPin1,0);
    }else if(readString == "rof"){
      digitalWrite(lMPin1,0);
    }else if(readString == "fof"){
      digitalWrite(lMPin1,0);
      digitalWrite(rMPin1,0);
    }
    if (readString.length()> 3 ){
      String srvVal = readString.substring(3);
     srv.write(srvVal.toInt());

    }
  readString = "";  
  }
  
}
