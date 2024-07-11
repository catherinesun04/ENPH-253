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

    testBackwardStop(driveSpeed, reflectanceSensorLeftPin, reflectanceSensorRightPin);

    delay(4000);
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

void testBackwardStop(int speed, int leftSensorPin, int rightSensorPin) {
    // Phase 1: Reverse until centered on the line
    bool rotating = false;
    while (true) {
        if (!rotating) {
            int leftSensorValue = readReflectanceSensor(leftSensorPin);
            int rightSensorValue = readReflectanceSensor(rightSensorPin);
            Direction dir = determineDirection(leftSensorValue, rightSensorValue);

            if (dir == CENTERED) {
                stopRobot();
                Serial.println("Robot is centered on the line, time to rotate");
                rotate180();
                rotating = true; // Move to the next phase
                delay(1000); // Give time for rotation
            } else {
                Serial.println("Robot hasn't reached the line yet, continuing reverse");
                driveBackward(speed);
            }
        } else {
            // Phase 2: Drive forward after rotating
            driveForward(speed);
            delay(1000); // This will not be time determined, insted we are using the input from the microswitch.
            stopRobot();
            Serial.println("Robot has reached the next counter, stopping.");
            break;
        }
        delay(50);
    }
}
