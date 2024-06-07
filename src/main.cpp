#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "frequency/frequencyDetect.h"
#include <cmath>


#define LED PC13

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin 
//#define SWITCH PA0


#define AIN_PIN PA3_ALT0
#define PWM_MAX 65535

volatile uint16_t PWM_VALUE= 0;
volatile double PWM_RATIO = 0.0;
volatile double INPUT_VOLTAGE = 0.0;

Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void switch_Press();


void setup() {

  pwm_start(PA_0, 500, 0, TimerCompareFormat_t::RESOLUTION_16B_COMPARE_FORMAT); //starts up PWM


  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C); //activates teh oLED


  display_handler.println("STARTING"); //message to see if the code is running
  display_handler.display();

  delay(1000);

}

void loop() {
  runMotor();
  displayPrep();

  display_handler.println("STARTING");
  display_handler.println("Input Voltage: " + String(INPUT_VOLTAGE)); //prints input voltage
  display_handler.println("Percentage: " + String(PWM_RATIO * 100) + "%"); //prints the percentage of power
  display_handler.println(PWM_VALUE); //prints duty cycle
  display_handler.display();
  
};





void runMotor() {
  INPUT_VOLTAGE = analogRead(PA3_ALT0)*3.30/1023.0; //calculates the input voltage
  PWM_RATIO = INPUT_VOLTAGE/ 3.30; //finds the ratio of the input voltage to 3.3V
  PWM_VALUE = PWM_RATIO * PWM_MAX; //calculates the duty cycle
  pwm_start(PA_0, 500, PWM_VALUE, TimerCompareFormat_t::RESOLUTION_16B_COMPARE_FORMAT);//changes PWM
}

void displayPrep() {//function that just stores lines of code
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
}