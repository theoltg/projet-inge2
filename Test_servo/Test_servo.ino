#include <Servo.h>
Servo servoMoteur;
void setup() {

  servoMoteur.attach(3);
  Serial.begin(9600);  

}

void loop() {
  servoMoteur.write(180);

}
