#include <Servo.h>

Servo myServo;
int const potPin = A0;
int potVal;
int angle;
int lastAngle =0;  
float smoothAngle =0;
unsigned long lastPrint =0;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);

}

void loop() {
  potVal = analogRead(potPin); 
   angle = map(potVal,0,1023,0,179);
  smoothAngle = (0.8* smoothAngle) + (0.2 * angle);

   //to reduce potentiometer noise
  if (abs(smoothAngle- lastAngle) >2) {
   myServo.write((int)smoothAngle);
   lastAngle = smoothAngle;
  }

  //myServo.write(angle);  // temporary test

  if(millis()-lastPrint > 100 ){        //makes serial monitor output legible
      Serial.print("potVal: ");
      Serial.print(potVal);
      Serial.print(", angle: ");
      Serial.print(angle);
      Serial.print(", smoothAngle: ");
      Serial.println((int)smoothAngle);
      lastPrint = millis();
  }

  // Serial.print("potVal: ");
  //     Serial.print(potVal);
  //     Serial.print(", angle: ");       //test
  //     Serial.print(angle);
  //     Serial.println();

  delay(25);

}
