#include <LiquidCrystal.h>

const int led = 13;             //pin for led
const int button = 12;          //pin for button
boolean prevButton = LOW;       //previous button state
boolean currentButton = LOW;    //current button state
boolean OFF = false; 
boolean ledState = OFF;         //state of LED
int ADCval = 1;                 //value for analog reading of POT
const int POT = A0;             //analog pin value for Potientiometer   
int PWMval;                     //initializing pwm variable for POT
const int pwm = 11;             
const int in2 = 9;
const int in1 = 10;
float voltage;
const int encoderPinA = 1;
const int encoderPinB = 8;
int encoderAState;
int encoderAPrevState;
int angle = 0;
int counter = 0;


LiquidCrystal lcd(7,6,5,4,3,2); //pins arduino in rel.to RS,EN,D4,D5,D6,& D7 on LCD        

boolean debounce(boolean prev);
int readPot(int POT); 
void getEncoder();

void setup() {
  pinMode(led, OUTPUT);   //led as output, button and encoder A & B inputs by default
  Serial.begin(9600);     //communication speed
  lcd.begin(16,2);         
    
}

void loop() {
  //for (int i=0; i<256; i++){ //test led to fade
  //  analogWrite(led, i);
  //  delay(10);
  //}
  //for (int i=255; i>=0; i--){
  //  analogWrite(led, i);
  //  delay(10);
  //} 
  currentButton = debounce(prevButton);              //weird delay in the button
  if (prevButton == LOW && currentButton == HIGH){
    ledState = !ledState;
  }
  prevButton = currentButton;
  digitalWrite(led, ledState);                       
  //delay(450);                                        //delay to read ADC values at 450ms (0-1023)
  ADCval = readPot(POT);
  voltage = 5*ADCval/1023;
  PWMval = ADCval/4;
  digitalWrite(in1, currentButton);
  digitalWrite(in2, !currentButton);
  analogWrite(pwm,PWMval);
  Serial.println(voltage);                             //checking voltage value from POT
  getEncoder();
  //lcd.setCursor(0,0);
  //lcd.print(String("PWM value: ") + String(PWMval)); //shows ADC values on LCD
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(String("Volt: ") + String(voltage) + String(" Deg: ") + String(int(angle*(-1.8)))); //shows voltage on LCD
  //digitalWrite(in1, currentButton);
  //digitalWrite(in2, !currentButton);
  //analogWrite(pwm, PWMval);
  }

boolean debounce(boolean previous){
  boolean currentButtonState = digitalRead(button);  //read button state
  if (previous != currentButtonState){
    delay(10);                                    //delay 10ms
    currentButtonState = digitalRead(button);
  return currentButtonState;
  }
}

int readPot(int POT){
  ADCval = analogRead(POT);
  return ADCval;
}

void getEncoder(){
  encoderAState = digitalRead(encoderPinA);
  if (encoderAState != encoderAPrevState){
    if (digitalRead(encoderPinB) != encoderAState){
      counter++;
      angle ++;
    }
    else{
      counter--;
      angle--;
    }
    if (counter >=30){
      counter = 0;
  }
  encoderAPrevState = encoderAState;
 }
}
