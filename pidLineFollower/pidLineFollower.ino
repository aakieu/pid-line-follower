//////////////////////////////////////////////////////////
//  Name      : EE444 Lab 06 
//  Author    : Cuong Kieu 
//  Date      : December 13 2018 
//  Version   : 1.0 
//////////////////////////////////////////////////////////


// include libraries
#include "maze.h"
// QRE1113 Reflective Object Sensor Input to Pro Micro
#define IR_ZERO 14  // (A0)
#define IR_ONE 15  // (A1)
#define IR_TWO 16  // (A2)
#define IR_THREE 17  // (A3)
#define IR_FOUR 18  // (A4)
// LED Inputs to Pro Micro
#define LED_ZERO 2  // 
#define LED_ONE 13  // 
#define LED_TWO 12 //
#define LED_THREE 11 // 
#define LED_FOUR 10 //
// HC-020K Double Speed Encoder 
#define ENCODER_LEFT A5
// Pro Micro output to TB6612FNG Motor Driver 
#define AIN1 4  // Right Motor 
#define AIN2 5  // 
#define PWMA 6  // 
#define BIN1 7  // Left Motor
#define BIN2 8  // 
#define PWMB 9  // 
#define STBY 3  //

// TB6612FNG OUTPUT TO MOTOR
//-----------------------------------
// A01 -- Blue Wire of Right Motor 
// A02 -- Yellow Wire of Right Motor 
// B01 -- Orange Wire of Left Motor 
// B02 -- Green Wire of Left Motor 
//-----------------------------------

// Variables for encoder 
int counter = 0;
const int rightClick = 17; 
const int leftClick = 14;
const int turnAroundClick = 34; 
// Initial motor speeds 
const uint8_t leftInitSpeed = 129;
const uint8_t rightInitSpeed = 140;
// Variables to keep track of intersection 
int numIntersection = 0; 
bool intersection = 0;
// Variables for PID Control
int previousError = 0; 
int PIDvalue = 0; 
int error = 0; 
int P = 0; 
int I = 0; 
int D = 0;
// Gain constants 
int Kp = 33;  // proportional  
int Ki = 0;  // integral
int Kd = 0;  // derivate

///////////////////////////////////////////////////// setup() /////////////////////////////////////////////////////////////
void setup()
{// Put code here to run once:
  Serial.begin (9600);  // for serial communication 
  init3Dot();  // initialize all input/output pins
  motorsOn();  // sets STBY to HIGH for both motors  
  blinkLed(5);
  };

///////////////////////////////////////////////////// loop() /////////////////////////////////////////////////////////////
void loop() 
{ // put your main code here, to run repeatedly:
  followLine();
  //displayIrData();
  //forward();
   
}; // end loop




 
  
