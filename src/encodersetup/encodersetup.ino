#include <LiquidCrystal.h>

const int pwm = 11;                   //pwm pin set at 11 
const int in2 = 9;                //digital i/o pin set to 9 
const int in1 = 10;               //digital i/o pin set to 10 
const int encoderPinA = 3;        //I/O pin for encoder A
const int encoderPinB = 2;        //I/O pin for encoder B
int encoderAState;                //state of encoder a pin
int encoderAPrevState;            //for previous encoder a state
int counter = 0;                  
int angle = 0;                    
LiquidCrystal lcd(22,23,24,25,26,27); //pins arduino in rel.to RS,EN,D4,D5,D6,& D7 on LCD        

//void getEncoder(); 

void setup() {
  Serial.begin(9600);     //communication speed, encoder pins inputs as default
  pinMode(pwm, OUTPUT);   //pwm set as output
  pinMode(in1, OUTPUT);   //logic pin 1 set as output
  pinMode(in2, OUTPUT);   //logic pin 2 set as output
  lcd.begin(16,2);
}

void loop() {
  digitalWrite(in1, HIGH); //clockwise motion
  digitalWrite(in2, LOW);
  analogWrite(pwm, 128);   //50% duty cycle
  //getEncoder();
  delay(3000);             //delay 3 secs
  lcd.clear();
  lcd.setCursor(0,0);
  //lcd.print(String("Degrees: ") + String(angle*(-1.8)));

  //digitalWrite(in1, LOW); //counterclockwise motion
  //digitalWrite(in2, HIGH);
  //analogWrite(pwm, 128);
  //getEncoder();
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print(String("Degrees: ") + String(angle*(-1.8)));
  //delay(3000);
}

void getEncoder(){
  encoderAState = digitalRead(encoderPinA);           //read encoder A pin
  if (encoderAState != encoderAPrevState){            //check current to prev state
    if (digitalRead(encoderPinB) != encoderAState){   //check encoder A and B are different
      counter++;                                      //increment counter 
      angle ++;                                       //increment angle (clockwise)
    }
    else{                                             //encoder A and B same
      counter--;                                      //deincrement counter
      angle--;                                        //deincrement angle (counterclockwise)
    }
    if (counter >=30){                                //setting limits for incrementing
      counter = 0;
  }
  encoderAPrevState = encoderAState;                  //make previous state the current state before going thru again
 }
}


