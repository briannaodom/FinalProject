#include <LiquidCrystal.h>

const int led = 13;             //pin for led
const int button = 12;          //pin for button
boolean prevButton = LOW;       //previous button state
boolean currentButton = LOW;    //current button state
boolean OFF = false; 
boolean ledState = OFF;         //state of LED
int ADCval = 1;                 //value for analog reading of POT
const int POT = A0;             //analog pin value for Potientiometer   
LiquidCrystal lcd(8,7,6,5,4,22); //pins arduino in rel.to RS,EN,D4,D5,D6,& D7 on LCD        

boolean debounce(boolean prev);

void setup() {
  pinMode(led, OUTPUT); //led as output, button input by default
  Serial.begin(9600);   //communication speed
  lcd.begin(16,2);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Hey");
}
