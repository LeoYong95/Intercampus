#include <Servo.h>
Servo srv;
int leftledPin = 3;
int rightledPin = 6;
int forwardledPin = 7;
String readString;


void setup() {
  Serial.begin(9600);
  srv.attach(5);
  pinMode(leftledPin, OUTPUT);
  pinMode(rightledPin, OUTPUT);
  pinMode(forwardledPin, OUTPUT);

}

void loop() {
  
  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  
  if (readString.length() >0) {
    Serial.println(readString);

    if(readString == "left"){
      digitalWrite(leftledPin,HIGH);
    }else if(readString == "right"){
      digitalWrite(rightledPin,HIGH);
    }else if(readString == "forward"){
      digitalWrite(forwardledPin,HIGH);
    }else if(readString == "leftoff"){
      digitalWrite(leftledPin,LOW);
    }else if(readString == "rightoff"){
      digitalWrite(rightledPin,LOW);
    }else if(readString == "forwardoff"){
      digitalWrite(forwardledPin,LOW);
    }

    if (readString.length()> 3 ){
      String srvVal = readString.substring(3);
     srv.write(srvVal.toInt());

      
    }
  readString = "";  
  }
  
}
