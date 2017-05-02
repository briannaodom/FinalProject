const int led = 13;          //pin for led
const int button = 12;       //pin for button
boolean prevButton = LOW;    //previous button state
boolean currentButton = LOW; //current button state
boolean OFF = false; 
boolean ledState = OFF;      //state of LED
int ADCval = 1;              //value for analog reading of POT
const int POT = A0;          //analog pin value for Potientiometer           

boolean debounce(boolean prev);

void setup() {
  pinMode(led, OUTPUT); //led as output, button input by default
  Serial.begin(9600);   //communication speed
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
  currentButton = debounce(prevButton);             //weird delay in the button
  if (prevButton == LOW && currentButton == HIGH){
    ledState = !ledState;
  }
  prevButton = currentButton;
  digitalWrite(led, ledState);
  ADCval = readPot(POT);
  Serial.println(ADCval);
  delay(450);                     //delay to read ADC values at 450ms (0-1023)
    
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

