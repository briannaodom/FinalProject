const int currentAnalog = A1;  //analog pin to get current
const int pwm = 11;            //pwm pin set to 11
const int in2 = 9;             //hbridge pin 
const int in1 = 10;            //hbridge pin
const int encoderPinA = 1;     //encoder A pin
const int encoderPinB = 8;     //encoder B pin 
volatile int encoderPos = 0;   
int prevEncoderPos = 0;    
int sensorVal;
float voltage;
int error;
int dError;
int desiredCurrent;
int measCurrent;
int eint;
int eprev;
int prevPWM; 
int propGain;
int integralGain;
int derivGain;
int PIDval = 65;        
int FALSE = 0; 
int stopAb;
int torque;
int prevTorque;
void incCurrent();
int getCurrent(int sensorVal);
void getEncoder();

void setup() {
  pinMode(currentAnalog, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
  analogWrite(pwm, 0);                   //motor at rest (0% duty)

  digitalWrite(encoderPinA, HIGH);       //interrupt
  digitalWrite(encoderPinB, HIGH);
  attachInterrupt(0, getEncoder, CHANGE);

}

void loop() {
 getVoltage();
 if (checkEncoder == 1){
   desiredCurrent = slope*encoderPos;     //spring
 }
 checkEncoder != checkEncoder;

}

void incCurrent(){
   error = desiredCurrent - measCurrent;   //proportional gain
 
   if (error <= 0.01 || error >= 0.01) {
    dError = error - errorPrev;
    eint = eint + error; 
    newCurrent = propGain * error;
    eprev = error;
    voltOfMotor = newCurrent/2;
    newCurrent = PWMprev + voltOfMotor*255;
    PWMprev = newCurrent;

    if (newCurrent < -255){               //add limits
      newCurrent = -255;
    }
    else if (newCurrent > 255){
      newCurrent = 255;
    }

    if (torque > //someval) {
      stopAb != FALSE; 
   }
    if (stopAb) {
      analogWrite(pwm, 0);                //abwheel stops
    }
    else if (newCurrent >= 0){
      digitalWrite(in1, LOW);
      analogWrite(pwm, newCurrent);
    }
    else {
      digitalWrite(in1, HIGH);
      newCurrent = -newCurrent;
      analogWrite(pwm, newCurrent);
    }
}

//will write more safeties and have to figure out torque equations 
//(sum of moments * acceleration)

void getCurrent(int PIDval){
  sensorVal = analogRead(currentAnalog);  //read analog
   voltage = 5*(sensorVal/1023);           //convert analog val (0-1023) to voltage (0V-5V);
  //Serial.println(sensorVal); 
   Serial.println(voltage);                //print voltage
   current = (voltage/PIDval-2.5/PIDval)*(1/0.015);
   return current;
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



