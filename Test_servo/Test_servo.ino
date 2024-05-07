#include <Servo.h>

  //Defintion du servomoteur
Servo servoMoteur; 
int pinServo=2;

void setup() {
  servoMoteur.attach(pinServo);
  Serial.begin(9600);  
}

void loop() {
    //Tourne a 180° et attend 10s
  servoMoteur.write(2,180);
  delay(10000);
  servoMoteur.write(2,65);
  delay(10000);

}
