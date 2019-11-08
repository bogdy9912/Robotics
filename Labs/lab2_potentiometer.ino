const int potPin = A0;
int potValue = 0;
int voltageValue = 0;
const int ledPin = 9;
int brightness = 0;
int fadeAmount = 5;
int ledValue = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(potPin, INPUT);
pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin);
  voltageValue = potValue * (5.0 / 1023);

  ledValue = map(potValue,0,1023,0,255);
    Serial.println(ledValue);
  analogWrite(ledPin,ledValue);

}
