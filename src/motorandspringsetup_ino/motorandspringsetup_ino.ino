#include <LiquidCrystal.h>

const int encoderPinA = 3;
const int encoderPinB = 2;
const int POT = A0;
const int in2 = 9;
const int in1 = 10;
const int pwm = 11;
int ADCval;
int ADCval2;
int k;
int counter = 0;
int angle = 0;
int aPinState;
int bPinState;
int currentPin = A1; 
int voltage;
int current;
int desiredCurrent;
int voltVal;
int currentGain = 67; //FIGURE OUT CURRENT GAIN!!!
//int prevButton = LOW;
//int currentButton = LOW;
//boolean OFF = false;
//boolean motorState = OFF;
int motorState = HIGH;                   //current state of output pin
unsigned long prevDebounceTime;            //last time output pin toggled in ms
unsigned long debounceDelay = 50;          //debounce time which increases if output flickers
LiquidCrystal lcd(7,6,5,4,8,22);


int setValueOfK(int POT){                //setting up potientiometer for spring constant that will be increased for higher resistance
  ADCval = analogRead(POT);
  k = map(ADCval, 0, 1023, 0, 100);
  return k; 
}


void rotateCW(){ 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
}

void rotateCCW(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
}

int calculateCurrent(int voltVal){
  ADCval2 = analogRead(currentPin);
  voltage = 5.0*(ADCval2/1023.0);
  current = ((voltage-2.5)/currentGain)/0,015;
  return current;
}
  
  
void encoder(){
  aPinState = digitalRead(encoderPinA);
  bPinState = digitalRead(encoderPinB);  
  if (bPinState != aPinState) {          //rotating clockwise if diff
       counter ++;
    }
  else {
      counter --;                       //rotating counterclockwise
    }
}


void setup() {
  Serial.begin(9600);
  pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);   //for control of hbridge
  pinMode(in2, OUTPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(encoderPinA, LOW);
  pinMode(encoderPinB, LOW);
  lcd.begin(16,2);
  digitalWrite(in1, motorState);
  digitalWrite(in2, motorState);            //set initial motor state
  attachInterrupt(0, encoder, CHANGE);      //interrupt for encoder
}

void loop() {
    //analogWrite(pwm, 320);
    //rotateCCW();
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(String("encoder:") + String(counter));
    k = setValueOfK(POT);                  //spring constant for spring equation
    lcd.setCursor(0,0);
    lcd.print(String("k:") + String(k));
    current = calculateCurrent(voltVal);
    lcd.setCursor(7,0);
    lcd.print(String("curr:") + String(current));
    desiredCurrent = k*counter;
    delay(2000);
}
