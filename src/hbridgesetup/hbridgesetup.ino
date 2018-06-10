#include <LiquidCrystal.h>

const int pwm = 11;     
const int in2 = 9;
const int in1 = 10; 
int ADCval = 1;                 //value for analog reading of POT
const int POT = A0;             //analog pin value for Potientiometer 
int PWMval;
LiquidCrystal lcd(22,23,24,25,26,27);

int readPot(int POT);

void setup() {
pinMode(pwm, OUTPUT); //pwm set as output
pinMode(in1, OUTPUT); //logic pin 1 set as output
pinMode(in2, OUTPUT); //logic pin 2 set as output
lcd.begin(16,2);

}

void loop() {

ADCval = readPot(POT);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(ADCval);
PWMval = ADCval/4;

analogWrite(pwm, PWMval);
digitalWrite(in2, HIGH);    //clockwise motion
digitalWrite(in1, LOW);
delay(3000);  //clockwise for 3 secs

digitalWrite(in1, HIGH); //brake 
digitalWrite(in2, HIGH);
delay(2000);  //brake for 3 secs

digitalWrite(in1, LOW); //counterclockwise motion
digitalWrite(in2, HIGH); 
delay(2000);  //counterclockwise for 3 secs

digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
delay(1000);
}

int readPot(int POT){
  ADCval = analogRead(POT);
  ADCval = map(ADCval, 0, 1023, 0, 100);
  return ADCval;
}

