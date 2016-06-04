/* Babybot code for intercampus technical team
 * 
 *The following code is run on Arduino nano
 *The code function is to obtain data from serial communication via Bluetooth
 *and interpret the data to control 2 DC motor and a Servo
 */

#include <Servo.h>

//--------Declare objects
Servo srv;
int leftMotorPin = 3;
int rightMotorPin = 6;
int forwardledPin = 7;
String readString;

//-------------Setup Void
void setup() {
  Serial.begin(9600);
  srv.attach(5);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(forwardledPin, OUTPUT);

}

//-----------Loop Void
void loop() {
  //--------------------------Read Serial
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  //---------------------------Execute Command
  if (readString.length() >0) {
    Serial.println(readString);

    if(readString == "lon"){
      digitalWrite(leftMotorPin,HIGH);
    }else if(readString == "ron"){
      digitalWrite(rightMotorPin,HIGH);
    }else if(readString == "fon"){
      digitalWrite(forwardledPin,HIGH);
    }else if(readString == "lof"){
      digitalWrite(leftMotorPin,LOW);
    }else if(readString == "rof"){
      digitalWrite(rightMotorPin,LOW);
    }else if(readString == "fof"){
      digitalWrite(forwardledPin,LOW);
    }

    if (readString.length()> 3 ){
      String srvVal = readString.substring(3);
     srv.write(srvVal.toInt());

      
    }
  readString = "";  
  }
  
}
