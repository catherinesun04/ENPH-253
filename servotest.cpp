// servotest.cpp

#include <Arduino.h>
#include "robot_functions.h"

void setup() {
    Serial.begin(115200);
    initializeIOPins();
    Serial.println("Servo Test Setup complete.");
}

void loop() {
    testSetServoAngle(servo1Control, 0);
    delay(1000);
    testSetServoAngle(servo1Control, 90);
    delay(1000);
    testSetServoAngle(servo1Control, 180);
    delay(1000);
    
    testSetServoAngle(servo2Control, 0);
    delay(1000);
    testSetServoAngle(servo2Control, 90);
    delay(1000);
    testSetServoAngle(servo2Control, 180);
    delay(1000);

    // Loop indefinitely for continuous testing
    while (true);
}

// Testing the setting of servo angle for a given ServoControl object and angle
void testSetServoAngle(ServoControl &servoControl, int angle) {
    setServoAngle(servoControl, angle);
    int currentAngle = getServoAngle(servoControl);
    Serial.print("Set servo to angle ");
    Serial.print(angle);
    Serial.print(". Current angle: ");
    Serial.println(currentAngle);
}
