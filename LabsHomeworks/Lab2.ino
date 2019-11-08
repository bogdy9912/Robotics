const int potPin1 = A0;
int potValue1 = 0;
const int ledPinRed= 9;
int ledValueRed = 0;

const int potPin2 = A1;
int potValue2 = 0;
const int ledPinGreen = 10;
int ledValueGreen = 0;

const int potPin3 = A2;
int potValue3 = 0;
const int ledPinBlue = 11;
int ledValueBlue = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(potPin1, INPUT);
pinMode(ledPinRed, OUTPUT);

pinMode(potPin2, INPUT);
pinMode(ledPinGreen, OUTPUT);

pinMode(potPin3, INPUT);
pinMode(ledPinBlue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
potValue1 = analogRead(potPin1);
ledValueRed = map(potValue1,0,1023,0,255);
analogWrite(ledPinRed,ledValueRed);

potValue2 = analogRead(potPin2);
ledValueGreen = map(potValue2,0,1023,0,255);
analogWrite(ledPinGreen,ledValueGreen);

potValue3 = analogRead(potPin3);
ledValueBlue = map(potValue3,0,1023,0,255);
analogWrite(ledPinBlue,ledValueBlue);
}
