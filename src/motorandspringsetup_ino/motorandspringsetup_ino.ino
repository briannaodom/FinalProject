#include <LiquidCrystal.h>


const int encoderPinA = 3;              //encoder interrupt pin for encoder A
const int encoderPinB = 2;              //encoder interrupt pin for encoder B
const int POT = A0;                     //potientiometer for controlling spring constant
const int in2 = 10;                     //not needed 
const int in1 = 9;                      //input pin for motor direction
const int pwm = 11;                     //pwm pin for motor
int ADCval;                             //for pot
int ADCval2;                            //for voltage
float current;
float voltage;    
float error;                            //following few terms for PID
float error1;
float e_int = 0;
float e_int1 = 0;
float prev_error = 0;
float new_current;
float new_position;
float motorVoltage;
float d_error = 0;
float voltage2;
int new_PWM = 0;
int prev_PWM = 0;
int k;                                   //spring constant
//int TurnOffMotor = 0;
volatile long encoderPos = 0;
int angle = 0;
int aPinState;                           //states of encoder pins A and B
int bPinState;                              
int currentPin = A1; 
int desiredCurrent;
int desiredEncoderPos;                  
float voltVal;
int Prop_gain = 1;
int d_gain = 0.1;
int currentGain = 100;                   //gain that affects range of current
int motorState = HIGH;                   //current state of output pin;
LiquidCrystal lcd(8,7,6,5,20,21);        //lcd pin setup


int setValueOfK(int POT){                //setting up potientiometer for spring constant that will be increased for higher resistance
  ADCval = analogRead(POT);
  k = map(ADCval, 0, 1023, 0, 10);
  return k; 
}


void rotateCW(){                             //following method of direction
  digitalWrite(in1, LOW);              
  digitalWrite(in2, HIGH);
  //delay(100);  
}

void rotateCCW(){                    
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  //delay(100); 
}

void STOP(){                        
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH); 
  delay(100);  
}

void encoder(){
  aPinState = digitalRead(encoderPinA);
  bPinState = digitalRead(encoderPinB);  
  if (bPinState != aPinState ) {        //rotating clockwise if diff        counter = -counter;
    encoderPos ++;
  }
  else {
    encoderPos --;                     //rotating counterclockwise
  }
}

void encoder2(){                        //not being used since two interrupts weren't working
  aPinState = digitalRead(encoderPinA);
  bPinState = digitalRead(encoderPinB);  
  if (bPinState != aPinState ) {         //rotating clockwise if diff        counter = -counter;
    encoderPos ++;
  }
  else {
    encoderPos --;                     //rotating counterclockwise
  }
}

int calculateCurrent(int voltVal){                      //function for calculating current from voltage
  ADCval2 = analogRead(currentPin);
  voltage = 5000*(ADCval2/1024.0);                      //gives mV, https://circuits4you.com/2016/05/13/arduino-asc712-current/
  current = (voltage-512.0)/(currentGain*0.015);          //2.5 ACSoffset, 512 same as 2.5V, 1.5 = currentGain * 0.015 (value of resistor)
  // lcd.clear();
  //lcd.print(String("ADC:") + String(ADCval2));
  //lcd.setCursor(0,1);
  //lcd.print(String("voltage:"));
  //lcd.setCursor(9,1);
  //lcd.print(voltage);
  //lcd.setCursor(0,0);
  // lcd.print("curr:");

  // lcd.print(current);

  return current;
}

void currentController(){
  desiredEncoderPos = 0;                                 //desired position for motor to roll back to
  error = desiredEncoderPos - encoderPos;                //trying to get wheel to spin back to 0, as user pushes on it
  desiredCurrent = k*error; 
  // lcd.setCursor(6,0);
  // lcd.print("dC:");
  // lcd.print(desiredCurrent);
  error1 = desiredCurrent-current;                       //PID controller
  // lcd.setCursor(12,1);                        
  // lcd.print(error);

  //if (error1 <= -0.025 || error1 >= 0.025)
  d_error = error - prev_error;
  new_current = Prop_gain*error + d_gain*d_error;          //figure out prop gain
  //prev_error = error;
  //voltage2 = new_current/185.0;                         //185 mV/A, 1 for 20A Module, .66 for 30A Module
  new_PWM = new_current;//prev_PWM + voltage2*255.0;  
  lcd.setCursor(0,1);
  lcd.print(new_PWM);   
  prev_PWM = new_PWM;

  if (new_PWM > 255 ){
    new_PWM = 255;
  }
  else if (new_PWM < -255){
    new_PWM = -255;
  }
  
  if (new_PWM >= 0) {
    rotateCW();
    analogWrite(pwm, new_PWM);
  }
  else {
    rotateCCW();
    analogWrite(pwm, -new_PWM);
  }
}  


void setup() {
  Serial.begin(9600);
  pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);   //for control of hbridge
  pinMode(in2, OUTPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  lcd.begin(16,2);
  digitalWrite(in1, motorState);
  digitalWrite(in2, motorState);            //set initial motor state
  attachInterrupt(0, encoder, CHANGE);     //interrupt for encoder, 0 is for digital pin 2
  //attachInterrupt(1, encoder2, CHANGE);     //1 is for digital pin 3, if we want more resolution. having issues with 2 however
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("encoder: ");
  lcd.print(encoderPos);
  k = setValueOfK(POT);                  //spring constant for spring equation
  //lcd.setCursor(0,0);
  //lcd.print(String("k:") + String(k));
  current = calculateCurrent(voltVal);
  //lcd.setCursor(0,1);
  //lcd.print("curr:");
  //lcd.print(current);
  currentController();
  //analogWrite(pwm,200);
  //rotateCCW(); 
  //STOP();
  //rotateCW();
}

