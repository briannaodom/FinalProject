const int encoderPin1 = ;
const int encoderPin2 = ;
float encoderPos; 
float getEncoder;

void getEncoder(); 

void setup() {
  Serial.begin(9600);
  pinMode(encoderPin1, HIGH);
  pinMode(encoderPin2, HIGH);              //encoder pins inputs by default
  attachInterrupt(0, getEncoder, CHANGE);  //apply interrupt
}

void loop() {
  if (digitalRead(encoderPin1) != digitalRead(encoderPin2)){
    encoderPos += 1;
  }
  else{
    encoderPos -= 1; 
  }
}
