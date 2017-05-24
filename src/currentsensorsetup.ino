const int currentAnalog = A1;  //analog pin to get current
int sensorVal;
float voltage;

void setup() {
  pinMode(currentAnalog, OUTPUT);
  Serial.begin(9600);

}

void loop() {
 sensorVal = analogRead(currentAnalog);  //read analog
 voltage = 5*(sensorVal/1023);           //convert analog val (0-1023) to voltage (0V-5V);
//Serial.println(sensorVal); 
 Serial.println(voltage);                //print voltage
// current = (voltage - 2.5)/PIDval * (1/0.015);   
 
}
