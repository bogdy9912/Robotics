#include "LedControl.h" //  need the library
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

const int pinSW = 8;
const int pinX = A0;
const int pinY = A1;

int SwState;
int xValue = 0;
int yValue = 0;
int k = 1;

int thresholdMin = 400;
int thresholdMax = 600;

// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

void setup()
{
  Serial.begin(9600);
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(pinSW, INPUT_PULLUP);
}
int oky = 0;
int ok = 0;
int j = 4;
int i = 4;
void loop()
{ /*
    for (int row = 0; row < 8; row++)
    {
    for (int col = 0; col < 8; col++)
    {
     lc.setLed(0, col, row, true); // turns on LED at col, row
     delay(25);
    }
    }
    for (int row = 0; row < 8; row++)
    {
    for (int col = 0; col < 8; col++)
    {
     lc.setLed(0, col, row, false); // turns off LED at col, row
     delay(25);
    }
    }*/
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  SwState = digitalRead(pinSW);

  if (xValue > thresholdMin && xValue < thresholdMax)
    ok = 0;

  if (xValue > thresholdMax && ok == 0)
  {
    if (k == 0)
      lc.setLed(0, j, i, false); // turns off LED at col, row
    i--;
    ok = 1;

    lc.setLed(0, j, i, true); // turns off LED at col, row
  }
  else if (xValue < thresholdMin && ok == 0)
  {
    if (k == 0)
      lc.setLed(0, j, i, false); // turns off LED at col, row
    i++;
    ok = 1;
    lc.setLed(0, j, i, true); // turns off LED at col, row
  }

  if (yValue > thresholdMin && yValue < thresholdMax)
    oky = 0;

  if (yValue > thresholdMax && oky == 0)
  {
    if (k == 0)
      lc.setLed(0, j, i, false); // turns off LED at col, row
    j++;
    oky = 1;
    lc.setLed(0, j, i, true); // turns off LED at col, row

  }
  else if (yValue < thresholdMin && oky == 0)
  {
    if (k == 0)
      lc.setLed(0, j, i, false); // turns off LED at col, row
    j--;
    lc.setLed(0, j, i, true); // turns off LED at col, row
    oky = 1;

  }

  if (i > 7)
  {
    lc.setLed(0, j, i, false); // turns off LED at col, row
    i = 0;
    lc.setLed(0, j, i, true); // turns off LED at col, row
  }
  if (i < 0)
  {
    lc.setLed(0, j, i, false); // turns off LED at col, row
    i = 7;
    lc.setLed(0, j, i, true); // turns off LED at col, row
  }
  if (j > 7)
  {
    lc.setLed(0, j, i, false); // turns off LED at col, row
    j = 0;
    lc.setLed(0, j, i, true); // turns off LED at col, row
  }
  if (j < 0)
  {
    lc.setLed(0, j, i, false); // turns off LED at col, row
    j = 7;
    lc.setLed(0, j, i, true); // turns off LED at col, row
  }


  if (SwState == LOW)
  {
    k = !k;

  }
  Serial.println(SwState);

}
