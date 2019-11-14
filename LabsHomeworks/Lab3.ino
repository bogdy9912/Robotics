const int buzzerInPin = A0;
const int ledPin = 13;
const int buzzerOutPin = 10;
const int buttonPin = 4;

int buzzerValue = 0;
int ledState = LOW;
int buttonState = 1;
const int threshold = 1;
int currentTime = 0;
int timer = 0;
int ok=0;

void setup() {
  
  pinMode(buzzerInPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerOutPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buzzerValue = analogRead(buzzerInPin);

  if(buzzerValue!=0)
    Serial.println(buzzerValue);
  
  if (buzzerValue > threshold && ok == 0) 
  {
    ok=1;
    Serial.println("A batut ");  
    ledState = HIGH;
    timer=millis();
  }
    if ((millis()- timer) >= 5000 && ok == 1)
      tone(buzzerOutPin, 600);
      
    buttonState = digitalRead(buttonPin);
    
    if (buttonState == LOW && ok == 1)
      {
        noTone(buzzerOutPin);  
        ok=0;
        ledState=LOW;
      }
    digitalWrite(ledPin, ledState);
  }
