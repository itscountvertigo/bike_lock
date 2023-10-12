#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial HM10(10, 11);                  // Note that pin 10 is RX, pin 11 is TX, but they have to be wired to servo's TX and RX respectively (opposite ends!)
Servo lockServo;

String serialMessage;
//int servoPos = 0;
bool locked = true;

void setup() {
  HM10.begin(9600);
  lockServo.attach(9);
  lockServo.write(180);
  Serial.begin(19200);
}

void loop() {
  HM10.listen();

  while (HM10.available() > 0) {
    serialMessage = HM10.readStringUntil('\n');
    Serial.println(serialMessage);              // Debugging purposes only
    
  }
  
  if (serialMessage == 'U') {
    lockServo.write(90);                        // Make the servo move to the half-way position
    delay(1000);                                // Wait to be sure the servo and the spring did their work
    lockServo.write(180);                       // Close the servo again, so if the lock is pushed into a closing position it will be locked
                                                // Note that the specific servo movements may change, this is still a placeholder before testing
  }
  
  // add other commands such as linking an account or setting up a password (TODO)
}
