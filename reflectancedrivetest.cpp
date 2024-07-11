#include <Arduino.h>
#include "robot_functions.h"

// Define driving speeds
int driveSpeed = 300;
int crawlSpeed = 100;

void setup() {
    Serial.begin(115200);
    initializeMotorPins();
    initializeIOPins();
    Serial.println("Reflectance Drive Test Setup Complete.");
}

void loop() {
    // Testing the ability to stop on the line coming from the left
    testLeftStop(driveSpeed, reflectanceSensorLeftPin, reflectanceSensorRightPin);

    delay(4000);

    // Testing the ability to stop on the line coming from the right
    testRightStop(driveSpeed, reflectanceSensorLeftPin, reflectanceSensorRightPin);

    delay(4000); // Delay before repeating the tests
}

// Function to test driving left until the robot is centered on the line
void testLeftStop(int speed, int leftSensorPin, int rightSensorPin) {
    while (true) {
        int leftSensorValue = readReflectanceSensor(leftSensorPin);
        int rightSensorValue = readReflectanceSensor(rightSensorPin);
        Direction dir = determineDirection(leftSensorValue, rightSensorValue);

        if (dir == CENTERED) {
            stopRobot();
            Serial.println("Robot is centered on the line.");
            break;
        } else if (dir == LEFT) {
            Serial.println("Robot needs to move left.");
            driveLeft(crawlSpeed);
        } else if (dir == RIGHT) {
            Serial.println("Robot needs to move right.");
            driveRight(crawlSpeed);
        } else {
            Serial.println("Robot is not on the line, moving left.");
            driveLeft(speed);
        }
        delay(50); // Short delay to prevent overwhelming the motor control
    }
}

// Function to test driving right until the robot is centered on the line
void testRightStop(int speed, int leftSensorPin, int rightSensorPin) {
    while (true) {
        int leftSensorValue = readReflectanceSensor(leftSensorPin);
        int rightSensorValue = readReflectanceSensor(rightSensorPin);
        Direction dir = determineDirection(leftSensorValue, rightSensorValue);

        if (dir == CENTERED) {
            stopRobot();
            Serial.println("Robot is centered on the line.");
            break;
        } else if (dir == LEFT) {
            Serial.println("Robot needs to move left.");
            driveLeft(crawlSpeed);
        } else if (dir == RIGHT) {
            Serial.println("Robot needs to move right.");
            driveRight(crawlSpeed);
        } else {
            Serial.println("Robot is not on the line, moving right.");
            driveRight(speed);
        }
        delay(50); // Short delay to prevent overwhelming the motor control
    }
}
