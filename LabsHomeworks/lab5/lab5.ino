#include <LiquidCrystal.h>
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int Ve = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int pinSW = 10;
const int pinX = A2;
const int pinY = A1;

int SwState;
int xValue = 0;
int yValue = 0;

int thresholdMin = 400;
int thresholdMax = 600;

int cursorValue = 0;



int hs = 0;
int score = 0;
int highscore = 0;

int congrats = 0;

int set = 0;
int startingLevelValue = 0;
int level = 0;
int count = 0;
unsigned long startTime = 0;
int nr = 0;
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(pinSW, INPUT_PULLUP);
  // Print a message to the LCD.
  //  lcd.print("Start Game  ");
  pinMode(Ve, OUTPUT);
  lcd.setCursor(3, 0);
  lcd.print("Main Menu");

}

int i = 0;
int ok;
int p = 0;
int t = 0;

int state = 0;
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  SwState = digitalRead(pinSW);
  xValue = analogRead(pinX);

  analogWrite(Ve, 50);
  /* if (p==0)
    {lcd.setCursor(3,0);
    lcd.print("Main Menu:");
    // lcd.setCursor(-millis()/ 1000, 1);
    // print the number of seconds since reset:
    lcd.setCursor(2,1);
     lcd.print(".");
    lcd.setCursor(3,1);
    lcd.print("Start Game");
    lcd.print(">>");
    lcd.setCursor(16,1);
    lcd.print("High Score");
    lcd.print(">>");
    lcd.setCursor(29,1);
    lcd.print("<<Settings");
    p=1;
    }*/

  if (SwState == LOW)
  {
    delay(1000);
    startTime = millis();
    state++;
    t = 0;

  }

  if (state % 2 == 0) {
    lcd.clear();
    if (xValue > thresholdMin && xValue < thresholdMax)
      ok = 0;

    if (xValue > thresholdMax && ok == 0)
    {
      i++;
      ok = 1;


    }
    else if (xValue < thresholdMin && ok == 0)
    {
      i--;
      ok = 1;

    }
    lcd.setCursor(2, 1);

    if (i > 2)
      i = 0;
    if (i < 0)
      i = 2;



    lcd.setCursor(3, 0);

    lcd.print("Main Menu");
    lcd.setCursor(3, 1);
    if (i == 0)
    {



      lcd.print(">Start Game");
    }
    if (i == 1)
    {
      lcd.print(">High Score");
    }
    if (i == 2)

    {

      lcd.print(">Settings    ");
    }
  }
  if (state % 2)
  {

    lcd.clear();
    if (i == 0)
    {

      lcd.setCursor(0, 0);
      lcd.print("live:3");
      if (millis() - startTime > 5000 && t == 0)
      {
        nr++;
        t = 1;
      }
      lcd.print(" level:");
      lcd.print(nr);
      lcd.setCursor(3, 1);
      if (millis() - startTime > 10000)
      {
        lcd.print("congrats");
      }
      score = nr * 3;
    }
    if (i == 1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Score: ");
      lcd.print(score);
    }
    if (i == 2)
    {
      lcd.setCursor(0, 0);
      lcd.print("Marin Bogdan");
      lcd.setCursor(0, 1);
      lcd.print("level: ");
      if (xValue > thresholdMin && xValue < thresholdMax)
        ok = 0;

      if (xValue > thresholdMax && ok == 0)
      {
        nr++;
        ok = 1;


      }
      else if (xValue < thresholdMin && ok == 0)
      {
        nr--;
        ok = 1;

      }
      lcd.print(nr);
    }
  }
  Serial.println(startTime);

  //  lcd.print(millis() / 1000);
}
