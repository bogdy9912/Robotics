const int buzzerInPin = A0;
const int ledPin = 13;
const int buzzerOutPin = 10;


int buzzerValue = 0;
int ledState = 0;


const int threshold = 5;

void setup() {
  
  pinMode(buzzerInPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerOutPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  buzzerValue = analogRead(buzzerInPin);

  if(buzzerValue!=0)
    Serial.println(buzzerValue);
    
  if (buzzerValue > threshold) {
    Serial.println("A batut ");  
    ledState = !ledState;
    tone(buzzerOutPin, buzzerValue);
    digitalWrite(ledPin, ledState);
  }
  delay(1000);
  noTone(buzzerOutPin);
  delay(10);
}
