// robot_functions.cpp

#include "robot_functions.h"

// Define motor pins for the H-bridges on the ESP32
const int backRightMotorPin1 = 16;
const int backRightMotorPin2 = 17;
const int backLeftMotorPin1 = 18;
const int backLeftMotorPin2 = 19;
const int frontRightMotorPin1 = 21;
const int frontRightMotorPin2 = 22;
const int frontLeftMotorPin1 = 23;
const int frontLeftMotorPin2 = 25;

// Define PWM channels
const int backRightPwmChannel1 = 0;
const int backRightPwmChannel2 = 1;
const int backLeftPwmChannel1 = 2;
const int backLeftPwmChannel2 = 3;
const int frontRightPwmChannel1 = 4;
const int frontRightPwmChannel2 = 5;
const int frontLeftPwmChannel1 = 6;
const int frontLeftPwmChannel2 = 7;

// Define Rotate Time and Speed
const int rotateTime = 500;
const int rotateSpeed = 100;

// Define servo motor pins
const int servo1Pin = 26;
const int servo2Pin = 27;

// Define microswitch sensor pins
const int microswitch1Pin = 32;
const int microswitch2Pin = 33;
const int microswitch3Pin = 14;

// Define reflectance sensor pins
const int reflectanceSensorLeftPin = 34;
const int reflectanceSensorRightPin = 35;

// Define reflectance comparator thresholds
const int reflectanceThreshold = 400;
const int reflectanceDifferenceThreshold = 50;

// Define PWM frequency and resolution
const int pwmFrequency = 10000;
const int pwmResolution = 10;

// Create Servo objects and track current angles
ServoControl servo1Control;
ServoControl servo2Control;

// Function implementations
void initializeMotorPins() {
    pinMode(backRightMotorPin1, OUTPUT);
    pinMode(backRightMotorPin2, OUTPUT);
    pinMode(backLeftMotorPin1, OUTPUT);
    pinMode(backLeftMotorPin2, OUTPUT);
    pinMode(frontRightMotorPin1, OUTPUT);
    pinMode(frontRightMotorPin2, OUTPUT);
    pinMode(frontLeftMotorPin1, OUTPUT);
    pinMode(frontLeftMotorPin2, OUTPUT);

    ledcSetup(backRightPwmChannel1, pwmFrequency, pwmResolution);
    ledcSetup(backRightPwmChannel2, pwmFrequency, pwmResolution);
    ledcSetup(backLeftPwmChannel1, pwmFrequency, pwmResolution);
    ledcSetup(backLeftPwmChannel2, pwmFrequency, pwmResolution);
    ledcSetup(frontRightPwmChannel1, pwmFrequency, pwmResolution);
    ledcSetup(frontRightPwmChannel2, pwmFrequency, pwmResolution);
    ledcSetup(frontLeftPwmChannel1, pwmFrequency, pwmResolution);
    ledcSetup(frontLeftPwmChannel2, pwmFrequency, pwmResolution);

    ledcAttachPin(backRightMotorPin1, backRightPwmChannel1);
    ledcAttachPin(backRightMotorPin2, backRightPwmChannel2);
    ledcAttachPin(backLeftMotorPin1, backLeftPwmChannel1);
    ledcAttachPin(backLeftMotorPin2, backLeftPwmChannel2);
    ledcAttachPin(frontRightMotorPin1, frontRightPwmChannel1);
    ledcAttachPin(frontRightMotorPin2, frontRightPwmChannel2);
    ledcAttachPin(frontLeftMotorPin1, frontLeftPwmChannel1);
    ledcAttachPin(frontLeftMotorPin2, frontLeftPwmChannel2);
}

void initializeIOPins() {
    servo1Control.servo.attach(servo1Pin);
    servo2Control.servo.attach(servo2Pin);
    servo1Control.currentAngle = 90;
    servo2Control.currentAngle = 90;
    servo1Control.servo.write(servo1Control.currentAngle);
    servo2Control.servo.write(servo2Control.currentAngle);

    pinMode(microswitch1Pin, INPUT_PULLUP);
    pinMode(microswitch2Pin, INPUT_PULLUP);
    pinMode(microswitch3Pin, INPUT_PULLUP);
}

void setMotorSpeed(int pwmChannel1, int pwmChannel2, bool direction, int speed) {
    if (direction) {
        ledcWrite(pwmChannel1, speed);
        ledcWrite(pwmChannel2, 0);
    } else {
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, speed);
    }
}

void dynamicBrakeMotor(int pwmChannel1, int pwmChannel2) {
    int currentSpeed1 = ledcRead(pwmChannel1);
    int currentSpeed2 = ledcRead(pwmChannel2);

    if (currentSpeed1 > 0) {
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 1023);
    } else if (currentSpeed2 > 0) {
        ledcWrite(pwmChannel1, 1023);
        ledcWrite(pwmChannel2, 0);
    }

    delay(20);
    ledcWrite(pwmChannel1, 0);
    ledcWrite(pwmChannel2, 0);
}

void driveForward(int speed) {
    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, true, speed);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, true, speed);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, true, speed);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, true, speed);
}

void driveBackward(int speed) {
    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, false, speed);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, false, speed);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, false, speed);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, false, speed);
}

void driveLeft(int speed) {
    int adjustedSpeed = speed * 1.1;
    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, false, speed);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, true, adjustedSpeed);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, true, adjustedSpeed);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, false, speed);
}

void driveRight(int speed) {
    int adjustedSpeed = speed * 1.1;
    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, true, adjustedSpeed);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, false, speed);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, false, speed);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, true, adjustedSpeed);
}

void rotate180() {
    int speed = rotateSpeed;
    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, true, speed);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, false, speed);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, true, speed);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, false, speed);

    delay(rotateTime);

    setMotorSpeed(frontLeftPwmChannel1, frontLeftPwmChannel2, true, 0);
    setMotorSpeed(frontRightPwmChannel1, frontRightPwmChannel2, false, 0);
    setMotorSpeed(backLeftPwmChannel1, backLeftPwmChannel2, true, 0);
    setMotorSpeed(backRightPwmChannel1, backRightPwmChannel2, false, 0);
}

void stopRobot() {
    dynamicBrakeMotor(frontLeftPwmChannel1, frontLeftPwmChannel2);
    dynamicBrakeMotor(frontRightPwmChannel1, frontRightPwmChannel2);
    dynamicBrakeMotor(backLeftPwmChannel1, backLeftPwmChannel2);
    dynamicBrakeMotor(backRightPwmChannel1, backRightPwmChannel2);
}

void setServoAngle(ServoControl &servoControl, int angle) {
    servoControl.servo.write(angle);
    servoControl.currentAngle = angle;
}

int getServoAngle(ServoControl &servoControl) {
    return servoControl.currentAngle;
}

bool isMicroswitchPressed(int pin) {
    return digitalRead(pin) == LOW;
}

int readReflectanceSensor(int pin) {
    return analogRead(pin);
}

Direction determineDirection(int leftSensor, int rightSensor) {
    if (leftSensor >= reflectanceThreshold && rightSensor >= reflectanceThreshold) {
        return NOT_ON_LINE;
    } else if (abs(leftSensor - rightSensor) < reflectanceDifferenceThreshold) {
        return CENTERED;
    } else if (leftSensor < reflectanceThreshold && rightSensor >= reflectanceThreshold) {
        return LEFT;
    } else if (rightSensor < reflectanceThreshold && leftSensor >= reflectanceThreshold) {
        return RIGHT;
    } else if (leftSensor < rightSensor) {
        return LEFT;
    } else {
        return RIGHT;
    }
}
