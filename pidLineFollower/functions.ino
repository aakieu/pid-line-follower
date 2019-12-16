///////////////////////////////////////////////////// INITIALIZATION /////////////////////////////////////////////////////////////
void init3Dot() 
{ // Initialize 3Dot Pins  
  // IR Sensor Pins
  pinMode(IR_ZERO,INPUT);
  pinMode(IR_ONE,INPUT);   //PD0
  pinMode(IR_TWO,INPUT);   //PD1
  pinMode(IR_THREE,INPUT);    //PF4
  pinMode(IR_FOUR,INPUT);    //PF5     
  // LED Pins 
  pinMode(LED_ZERO,OUTPUT);  
  pinMode(LED_ONE,OUTPUT);  
  pinMode(LED_TWO,OUTPUT);  
  pinMode(LED_THREE,OUTPUT);   
  pinMode(LED_FOUR,OUTPUT);  
  // Encoder Pins 
  pinMode(ENCODER_LEFT,INPUT);
  //Motor Driver Pins 
  pinMode(AIN1,OUTPUT);   //PB5
  pinMode(AIN2,OUTPUT);  //PB6
  pinMode(PWMA,OUTPUT);   //PC6
  pinMode(BIN1,OUTPUT);   //PD4
  pinMode(BIN2,OUTPUT);   //PD7
  pinMode(PWMB,OUTPUT);   //PD6
};

///////////////////////////////////////////////////// IR SENSORS  /////////////////////////////////////////////////////////////
int * readSensor()
{ static int data[5];
  //Read in Data
  data[0] = digitalRead(IR_ZERO);
  data[1] = digitalRead(IR_ONE);
  data[2] = digitalRead(IR_TWO);
  data[3] = digitalRead(IR_THREE);
  data[4] = digitalRead(IR_FOUR);
  return data;};


void displayIrData()
{ // displays analogRead values of all 4 IR sensors via Serial Monitor 
  // Read in Input from Sensors
  int * LFSensor = readSensor(); 
  // Display on Serial Monitor  
  for(int i = 0;  i<5; i ++)
  { Serial.print("\t");
    Serial.print("Sensor ");
    Serial.print(i); 
    Serial.print(": ");
    Serial.print(LFSensor[i]);
    if (i ==4) 
    {Serial.print("\n"); delay(10);}
  }
}; // end displayIrData()

///////////////////////////////////////////////////// MOTOR SHAFT ENCODER  /////////////////////////////////////////////////////////////
bool readEncoderUntil (int clicks)
{  // reads encoder until a certain amount of clicks 
   // for the wooden cutout 40 clicks = one full revolution
  bool sensorVal = digitalRead(ENCODER_LEFT); 
  bool noChange = true; 
  while (noChange)
  { bool tempVal = digitalRead(ENCODER_LEFT);
    if (tempVal != sensorVal) 
    { counter +=1; 
      noChange = false;
    } 
  }      
  //Serial.println(counter);
  if (counter == clicks)
  { counter = 0; 
  return true;
  }
  else {return false;}; 
};


///////////////////////////////////////////////////// LEDs  /////////////////////////////////////////////////////////////
//turns on a particular led 
void turnOnLed(int ledNumber)
{ switch (ledNumber) 
  { case 0:
      digitalWrite(LED_ZERO,HIGH); 
      break;
    case 1:
      digitalWrite(LED_ONE,HIGH); 
      break;
    case 2:
      digitalWrite(LED_TWO,HIGH); 
      break;
    case 3:
      digitalWrite(LED_THREE,HIGH); 
      break;
    case 4:
      digitalWrite(LED_FOUR,HIGH); 
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
};

// turns off a particular led 
void turnOffLed(int ledNumber) 
{ switch (ledNumber) 
    {
    case 0:
      digitalWrite(LED_ZERO,LOW); 
      break;
    case 1:
      digitalWrite(LED_ONE,LOW); 
      break;
    case 2:
      digitalWrite(LED_TWO,LOW); 
      break;
    case 3:
      digitalWrite(LED_THREE,LOW); 
      break;
    case 4:
      digitalWrite(LED_FOUR,LOW); 
      break;  
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
    }
}; // end turnOffLed();

// Blinks outer red leds indefinitely 
void ledError()
{ while (true)
  { digitalWrite(LED_ZERO,HIGH);
    digitalWrite(LED_FOUR,HIGH);  
    delay(100);
    digitalWrite(LED_ZERO,LOW);
    digitalWrite(LED_FOUR,LOW); 
    delay(100);
  }
} // end ledError(); 

// turns on leds in order then turns off leds in order 
void countDown(int myDelay) 
{ for (int i = 0; i <= 4; i ++)
  { turnOnLed(i); 
    delay(myDelay);
  }
  for (int i = 0; i <= 4; i ++)
  { turnOffLed(i);
    delay(myDelay);
  }
};

// Turns off all leds 
void ledOff()
{ for (int i = 0; i <= 4; i ++) turnOffLed(i); }

//turns on all leds
void ledOn()
{ for (int i = 0; i <= 4; i ++) turnOnLed(i);  }

// blinks all leds n times 
void blinkLed(int n)
{ for (int i = 0; i <= n; i ++)
  { ledOn(); delay(250); 
    ledOff(); delay(250);
  }
}

///////////////////////////////////////////////////// MOTOR CONTROL  /////////////////////////////////////////////////////////////
// turns on motors
void motorsOn()
{
  digitalWrite(STBY,HIGH);
}

// turns off motors 
void motorsOff()
{
  digitalWrite(STBY,LOW); 
};

// Sets the right motor speed and direction 
void setRightMotor(bool dir, int motorSpeed)
{ // setting speed 
  motorsOn();
  analogWrite(PWMA,motorSpeed);  // x between 0-255 
  
  // sets direction as forward 
  if (dir == 1)
  {// left dir set to forward
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
  }

  // sets direction to reverse
  else if (dir == 0) 
  {
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
  }
  else
  ledError();  
};

// Sets the left motor speed and direction 
void setLeftMotor(bool dir, int motorSpeed)
{// Sets the speed of the
  motorsOn();
  analogWrite(PWMB,motorSpeed);  // x between 0-255
  // sets direction as forward for left motor 
  if (dir == 1)
  {// sets direction as forward for right motor 
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
  }
  else if (dir == 0) 
  {// sets direction as forwoard for right motor 
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
  }
  else 
  ledError();   
};
     
// moving forward
void forward()
{ 
  motorsOn();
  setRightMotor(1,rightInitSpeed); 
  setLeftMotor(1,leftInitSpeed); 
};

// stops motor
void brake()
{
  motorsOff(); 
};

// moves up a little 
void stepUp()
{ 
  motorsOn();
  setRightMotor(1,rightInitSpeed); 
  setLeftMotor(1,leftInitSpeed);
  delay(350); 
  motorsOff(); 
};

// Turn left using Encoder
void turnLeft()
{  
  setRightMotor(1,rightInitSpeed-10); 
  setLeftMotor(0,leftInitSpeed-10);
  motorsOn(); 
  while (true){
  bool clicksTrue = readEncoderUntil(leftClick);
  if (clicksTrue)
  {brake();
  break;}  
  }; 
}

//Turn right using Encoder
void turnRight()
{  
  setRightMotor(0,rightInitSpeed-10); 
  setLeftMotor(1,leftInitSpeed-10);
  motorsOn(); 
  while (true){
  bool clicksTrue = readEncoderUntil(rightClick);
  if (clicksTrue)
  {brake();
  break;}  
  }; 
}

// turns around in CW direction 
void turnAround()
{  
  setRightMotor(0,rightInitSpeed-10); 
  setLeftMotor(1,leftInitSpeed-10);
  motorsOn(); 
  while (true){
  bool clicksTrue = readEncoderUntil(turnAroundClick);
  if (clicksTrue)
  {brake();
  break;}  
  }; 
}

///////////////////////////////////////////////////// PID  /////////////////////////////////////////////////////////////
//return error 
int returnError(int LFSensor[5] )
{ int err;
    //Only far right sensor is on black
  if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 1 )) 
  { err = -3;
    //turn on equivalent led
    turnOnLed(4);}
  
  //Only inner right sensor is on black 
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0 )) 
  { err = -2;
    turnOnLed(3);}
    
  // Middle and inner right sensor is on black
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 0 )) 
  { err = -1;
    turnOnLed(2); 
    turnOnLed(3);}

  //Only middle sensor is on black
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) 
  { err = 0;
    turnOnLed(2);}

  // Middle and inner left sensor is on black
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) 
  { err = 1;
    turnOnLed(1); 
    turnOnLed(2);}

  // Inner left sensor is on black 
  else if((LFSensor[0]== 0 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 )) 
  { err = 2;
    turnOnLed(1);}

  // Only outer left is on black 
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 0 )&&(LFSensor[2]== 0 )&&(LFSensor[3]== 0 )&&(LFSensor[4]== 0 ))
  { err = 3;
    turnOnLed(0);}

  // INTERSECTION (All sensors are on black)
  else if((LFSensor[0]== 1 )&&(LFSensor[1]== 1 )&&(LFSensor[2]== 1 )&&(LFSensor[3]== 1 )&&(LFSensor[4]== 1 )) 
  { intersection = true;
    err = 0; 
    turnOnLed(4); 
    turnOnLed(0);}
  // Return error   
  return err;}

//calculates and returns PID error 
int calcPID(int error, int previousError)
{ 
  P = error;
  I= I + error;
  D = error-previousError;
  int pid = (Kp*P) + (Ki*I) + (Kd*D);
  return pid; 
};

// set motor speed based on PID error 
void setLeftRightSpeed(int PIDval)
{ int rightSpeed = rightInitSpeed + PIDval; 
  int leftSpeed = leftInitSpeed - PIDvalue; 
//  Serial.print("rightSpeed: ") ;
//  Serial.print(rightSpeed); 
//  Serial.print("\n");
//  Serial.print("leftSpeed: ") ;
//  Serial.print(leftSpeed); 
//  Serial.print("\n");
  setLeftMotor(1,leftSpeed); 
  setRightMotor(1,rightSpeed); };

// increments intersection after intersection is detected
void countIntersection()
{ while (intersection)
  { forward();  // Should you delete this line of code?
    if (!(digitalRead(IR_ZERO) && digitalRead(IR_FOUR)))
    { numIntersection+=1;  // put in return error code?
      break;
    }
  }
}

// follows straight line 
void followLine()
{ //Read Sensor  
  int * LFSensor = readSensor();
  //Error for PID  
  error = returnError(LFSensor); 
  // PID Calculation 
  PIDvalue = calcPID(error, previousError);
  previousError = error;
  // Set motor speeds based on error  
  Serial.print("PIDValue: ");
  Serial.print(PIDvalue); 
  Serial.print("\n");
  setLeftRightSpeed(PIDvalue); 
  // Turn off all leds 
  ledOff(); 
};//end followLine()
