const int led = 13; 
const int button = 12;
boolean prevButton = LOW;    //previous button state
boolean currentButton = LOW; //current button state
boolean OFF = false; 
boolean ledState = OFF;      //state of LED

boolean debounce(boolean prev);

void setup() {
  pinMode(led, OUTPUT); //led as output, button input by default
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
  currentButton = debounce(prevButton);
    if (prevButton == LOW && currentButton == HIGH){
      ledState = !ledState;
    }
    prevButton = currentButton;
    digitalWrite(led, ledState);
}


boolean debounce(boolean previous){
  boolean currentButtonState = digitalRead(button);  //read button state
  if (previous != currentButtonState){
    delay(10);                                    //delay 10ms
    currentButtonState = digitalRead(button);
  return currentButtonState;
  }
}
