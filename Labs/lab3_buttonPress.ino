const int buttonPin=2;

  int buttonValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);
  

}
