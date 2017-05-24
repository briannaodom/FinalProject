const int currentAnalog = A1;  //analog pin to get current
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
int PIDval;


void setup() {
  pinMode(currentAnalog, OUTPUT);
  Serial.begin(9600);

}

void loop() {
 sensorVal = analogRead(currentAnalog);  //read analog
 voltage = 5*(sensorVal/1023);           //convert analog val (0-1023) to voltage (0V-5V);
//Serial.println(sensorVal); 
 Serial.println(voltage);                //print voltage
 current = (voltage/PIDval-2.5/PIDval)*(1/0.015);   

error = desiredCurrent - measCurrent;     //proportional gain

if (error <= //someval || error >= someVal) {
 dError = error - errorPrev;
 eint = eint + error; 
 newCurrent = propGain * error;
 eprev = error;
 voltOfMotor = newCurrent /// someVal;
 newCurrent = PWMprev + voltOfMotor* //someval;
 PWMprev = newCurrent;

}
