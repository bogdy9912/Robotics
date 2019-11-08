const int ledPin = 13;
const int buttonPin = 2;

int buttonState = 0;
int ledState = 0;

int previousButtonState = 0;


int lastDebounceInterval = 0;
int debounceDelay = 50;

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:


  int reading = digitalRead(buttonPin);

    if (reading != previousButtonState)
    {
      lastDebounceInterval = millis();  
    }

    if (millis - lastDebounceInterval > debounceDelay)
      if (reading != buttonState)
      {
        buttonState = reading;

        if (buttonState == HIGH)
        {
          ledState = !ledState;
        }
        
      }

digitalWrite(ledPin,ledState);
previousButtonState = reading;
}
