const int led = 13; 
const int button = 2;

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
    if (digitalRead(button)== HIGH){ //test push button
      digitalWrite(led, HIGH);
    }
    else{
      digitalWrite(led,LOW);
  }
}
