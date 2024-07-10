// robot_functions.h

#ifndef ROBOT_FUNCTIONS_H
#define ROBOT_FUNCTIONS_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ESP32Servo.h>

// Define motor pins for the H-bridges on the ESP32
extern const int backRightMotorPin1;
extern const int backRightMotorPin2;
extern const int backLeftMotorPin1;
extern const int backLeftMotorPin2;
extern const int frontRightMotorPin1;
extern const int frontRightMotorPin2;
extern const int frontLeftMotorPin1;
extern const int frontLeftMotorPin2;

// Define PWM channels
extern const int backRightPwmChannel1;
extern const int backRightPwmChannel2;
extern const int backLeftPwmChannel1;
extern const int backLeftPwmChannel2;
extern const int frontRightPwmChannel1;
extern const int frontRightPwmChannel2;
extern const int frontLeftPwmChannel1;
extern const int frontLeftPwmChannel2;

// Define Rotate Time and Speed
extern const int rotateTime;
extern const int rotateSpeed;

// Define servo motor pins
extern const int servo1Pin;
extern const int servo2Pin;

// Define microswitch sensor pins
extern const int microswitch1Pin;
extern const int microswitch2Pin;
extern const int microswitch3Pin;

// Define reflectance sensor pins
extern const int reflectanceSensorLeftPin;
extern const int reflectanceSensorRightPin;

// Define reflectance comparator thresholds
extern const int reflectanceThreshold;
extern const int reflectanceDifferenceThreshold;

// Define PWM frequency and resolution
extern const int pwmFrequency;
extern const int pwmResolution;

// Create Servo objects and track current angles
struct ServoControl {
    Servo servo;
    int currentAngle;
};

// Function prototypes
void initializeMotorPins();
void initializeIOPins();
void setMotorSpeed(int pwmChannel1, int pwmChannel2, bool direction, int speed);
void dynamicBrakeMotor(int pwmChannel1, int pwmChannel2);
void driveForward(int speed);
void driveBackward(int speed);
void driveLeft(int speed);
void driveRight(int speed);
void rotate180();
void stopRobot();
void testRotate();
void setServoAngle(ServoControl &servoControl, int angle);
int getServoAngle(ServoControl &servoControl);
bool isMicroswitchPressed(int pin);
int readReflectanceSensor(int pin);
void testDetermineDirection(int leftSensorPin, int rightSensorPin);
void testReadReflectanceSensor(int sensorPin);
void testDriveForwardBackward();
void testDriveLeftRight();
void testRotate();


enum Direction {
    LEFT,
    RIGHT,
    CENTERED,
    NOT_ON_LINE
};

Direction determineDirection(int leftSensor, int rightSensor);

#endif // ROBOT_FUNCTIONS_H
