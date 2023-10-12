#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial HM10(10, 11);                // pins are probably going to change
Servo lockServo;

String serialMessage;
int servoPos = 0;
bool locked = true;

void setup() {
  HM10.begin(9600);
  lockServo.attach(9);
  lockServo.write(180);
  Serial.begin(19200);
}

void loop() {
  HM10.listen();
//  Serial.println(HM10.read());

  while (HM10.available() > 0) {
    serialMessage = HM10.readStringUntil('\n');
    Serial.println(serialMessage);
    
  }
  
  if (serialMessage == 'U') {
    lockServo.write(90);                      // Make the servo move to the half-way position
    delay(1000);                               // Wait to be sure the servo and the spring did their work
    lockServo.write(180);                     // Close the servo again, so if the lock is pushed into a closing position it will be locked
  }
  
  // add other commands such as linking an account or setting up a password (TODO)
}
/*
bool unlock() {
  // Returns 1 if successful, returns 0 if already locked:
  if (locked) {
    return false;
  }

  lockServo.write(90);                      // Make the servo move to the half-way position
  delay(100);                               // Wait to be sure the servo and the spring did their work
  lockServo.write(180);                     // Close the servo again, so if the lock is pushed into a closing position it will be locked

  return true;
}*/
