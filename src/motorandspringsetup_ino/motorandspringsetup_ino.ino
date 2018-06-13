#include <LiquidCrystal.h>
#include <PID_v1.h>

const int encoderPinA = 3;
const int encoderPinB = 2;
const int POT = A0;
const int in2 = 9;
const int in1 = 10;
const int pwm = 11;
int ADCval;
int ADCval2;
float current;
float voltage;
float error;
float e_int = 0;
float prev_error = 0;
float new_current;
float motorVoltage;
float d_error = 0;
float voltage2;
int new_PWM = 0;
int prev_PWM = 0;
int k;
int TurnOffMotor = 0;
volatile long counter = 0;
int angle = 0;
int aPinState;
int bPinState;
int currentPin = A1; 
int desiredCurrent;
float voltVal;
int Prop_gain = 1;                      //Figure Out!!
int currentGain = 100;                   //gain that affects range of current
int motorState = HIGH;                   //current state of output pin;
LiquidCrystal lcd(8,7,6,5,20,21);


int setValueOfK(int POT){                //setting up potientiometer for spring constant that will be increased for higher resistance
  ADCval = analogRead(POT);
  k = map(ADCval, 0, 1023, 0, 100);
  return k; 
}


void rotateCW(){ 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(1000);
}

void rotateCCW(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(1000);
}

void STOP(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  delay(1000);
}

void encoder(){
  aPinState = digitalRead(encoderPinA);
  bPinState = digitalRead(encoderPinB);  
  if (bPinState != aPinState ) {         //rotating clockwise if diff        counter = -counter;
        counter ++;
    }
    else {
        counter --;                     //rotating counterclockwise
    }
}

void encoder2(){
  aPinState = digitalRead(encoderPinA);
  bPinState = digitalRead(encoderPinB);  
  if (bPinState != aPinState ) {         //rotating clockwise if diff        counter = -counter;
        counter ++;
    }
    else {
        counter --;                     //rotating counterclockwise
    }
}

int calculateCurrent(int voltVal){
  ADCval2 = analogRead(currentPin);
  voltage = 5000*(ADCval2/1024.0);                      //gives mV, https://circuits4you.com/2016/05/13/arduino-asc712-current/
  current = (voltage-512)/(currentGain*0.015);          //2.5 ACSoffset, 512 same as 2.5V, 1.5 = currentGain * 0.015 (value of resistor)
  //lcd.clear();
  //lcd.print(String("ADC:") + String(ADCval2));
  //lcd.setCursor(0,1);
  //lcd.print(String("voltage:"));
  //lcd.setCursor(9,1);
  //lcd.print(voltage);
  //lcd.setCursor(0,0);
  //lcd.print("curr:");
  //lcd.print(current);
 
  return current;
}
  
void currentController(float current){
  desiredCurrent = k*current;
  error = desiredCurrent-current;
  
  if (error <= -0.025 || error >= 0.025)
   d_error = error - prev_error;
   e_int = e_int + error;
   new_current = Prop_gain*error;              //figure out prop gain
   prev_error = error;
   voltage2 = new_current/1.85;               //185 mV/A, 1 for 20A Module, .66 for 30A Module
   new_PWM = prev_PWM + voltage2*255;      
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
  //attachInterrupt(0, encoder, CHANGE);
  attachInterrupt(0, encoder, CHANGE);     //interrupt for encoder, 0 is for digital pin 2
  //attachInterrupt(1, encoder2, CHANGE);     //1 is for digital pin 3
}

void loop() {
    k = setValueOfK(POT);                  //spring constant for spring equation
    //lcd.setCursor(0,0);
    //lcd.print(String("k:") + String(k));
    current = calculateCurrent(voltVal);
    //lcd.setCursor(7,0);
    //lcd.print(String("curr:") + String(current));
    analogWrite(pwm,10);
    //rotateCW();
    //STOP();
    rotateCCW();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(String("encoder:") + String(counter));  //encoder counts correctly until motor spins to fast. need limit?
}
