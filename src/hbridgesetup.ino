const int pwm = 11;     
const int in2 = 9;
const int in1 = 10; 
int ADCval = 1;                 //value for analog reading of POT
const int POT = A0;             //analog pin value for Potientiometer 
int PWMval;

int readPot(int POT);

void setup() {
pinMode(pwm, OUTPUT); //pwm set as output
pinMode(in1, OUTPUT); //logic pin 1 set as output
pinMode(in2, OUTPUT); //logic pin 2 set as output

}

void loop() {

ADCval = readPot(POT);
Serial.println(ADCval);
PWMval = ADCval/4;

digitalWrite(in1, HIGH);    //clockwise motion
digitalWrite(in2, LOW);
analogWrite(pwm, PWMval);
delay(3000);  //clockwise for 3 secs

digitalWrite(in1, HIGH); //brake 
digitalWrite(in2, HIGH);
delay(3000);  //brake for 3 secs

digitalWrite(in1, LOW); //counterclockwise motion
digitalWrite(in2, HIGH); 
delay(3000);  //counterclockwise for 3 secs

digitalWrite(in1, HIGH);
digitalWrite(in2, HIGH);
delay(1000);
}

int readPot(int POT){
  ADCval = analogRead(POT);
  return ADCval;
}

