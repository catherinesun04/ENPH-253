// drivetest.cpp

#include <Arduino.h>
#include "robot_functions.h"

void setup() {
    Serial.begin(115200);
    initializeMotorPins();
    Serial.println("Drive Test Setup complete.");
}

void loop() {
    testDriveForwardBackward();
    testDriveLeftRight();
    testRotate();
}

// Testing for the forwards and backwards driving
void testDriveForwardBackward() {
    Serial.println("Testing forward and backward driving...");
    driveForward(100);
    delay(1000);
    stopRobot();
    delay(500);

    driveBackward(100);
    delay(1000);
    stopRobot();
    delay(500);
}

// Testing for the left and right driving
void testDriveLeftRight() {
    Serial.println("Testing left and right driving...");
    driveLeft(100);
    delay(1000);
    stopRobot();
    delay(500);

    driveRight(100);
    delay(1000);
    stopRobot();
    delay(500);
}

// Testing the rotate capabilities of the robot
void testRotate() {
    Serial.println("Testing rotate 180...");
    rotate180();
    delay(1000);
    stopRobot();
    delay(500);
}
