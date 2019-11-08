const int buzzerPin = 11;
const int photoCellPin = A0;
const int ledPin = 13;

int photoCellValue = 0;
int buzzerValue = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode (buzzerPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  photoCellValue = analogRead(photoCellPin);
  tone(buzzerPin,buzzerValue);
  delay(100);
  //noTone(buzzerPin);
  
  buzzerValue += 100;
  
  if (buzzerValue > 500)
    digitalWrite(ledPin, HIGH);
  
  if (buzzerValue < 400)
    digitalWrite(ledPin, LOW);
}
