const int buttonPin = 2;
const int ledPin = 13;
const int photoCellPin = A0; 


int ledState = 0;
int photoCellValue = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // min = 130, max = 750;

  if (photoCellValue < 140)
    digitalWrite(ledPin, HIGH);
  if (photoCellValue>160)
  digitalWrite(ledPin, LOW);
  photoCellValue = analogRead(photoCellPin);
  Serial.println(photoCellValue);
}
