#include "LedControl.h" //  need the library
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

const int pinSW = 8;
const int pinX = A0;
const int pinY = A1;
typedef struct projectile{
  int pozy;
  int pozx; 
  }projectile;
projectile bullet[8];
int SwState;
int prevSwState = 1;
int xValue = 0;
int yValue = 0;
int k = 1;

int thresholdMin = 400;
int thresholdMax = 600;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(pinSW, INPUT_PULLUP);
}
int i;
int index;
int man[8];
int col;
int row;
bool matrix[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};
bool player2[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};
int ok = 0;
int oky = 0;
byte start = 0;
int aux[8];


void  playerOneMove() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);


  if (xValue > thresholdMin && xValue < thresholdMax)
    ok = 0;

  if (xValue > thresholdMax && ok == 0)
  {
    if (row < 7)
    { matrix[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      row++;
      matrix[row][col] = 1;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row
      ok = 1;
    }
  }
  else if (xValue < thresholdMin && ok == 0)
  {
    if (row > 0)
    {
      matrix[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      row--;
      matrix[row][col] = 1;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row
      ok = 1;
    }
  }

  if (yValue > thresholdMin && yValue < thresholdMax)
    oky = 0;

  if (yValue > thresholdMax && oky == 0)
  {
    if (col < 3)
    {
      matrix[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      col++;
      matrix[row][col] = 1;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row

      oky = 1;
    }
  }
  else if (yValue < thresholdMin && oky == 0)
  {
    if (col > 0)
    {
      matrix[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      col--;
      matrix[row][col] = 1;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row
      oky = 1;
    }
  }
  /*
    if (row > 7)
    {
      row = 7;
      matrix[row][col] = 1;
      lc.setLed(0, col, row, matrix[row][col]); // turns off LED at col, row
    }
    if (row < 0)
    {
      row = 0;
      matrix[row][col] = 1;
      lc.setLed(0, col, row, matrix[row][col]); // turns off LED at col, row
    }


    if (col > 3)
    {
      col = 3;
      matrix[row][col] = 1;
      lc.setLed(0, col, row, matrix[row][col]); // turns off LED at col, row
    }
    if (col < 0)
    {
      col = 0;
      matrix[row][col] = 1;
      lc.setLed(0, col, row, matrix[row][col]); // turns off LED at col, row
    }*/
}

void animationStart(int start) {
  if (start == 0)
  { for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(0, row, col, matrix[row][col]);
      }
    }
    start = 1;
  }
}

int shootFreq(int i) {
  if (millis() - aux[i] >= 2000) {
    {
      return 1;
      aux[i] = millis();
    }
  }
}


void getShootPositions() {
  if (SwState == 0 && SwState != prevSwState)
  {

    prevSwState = SwState;
    man[row] += 1;
    aux[row] += 1;
  }
}

void realShootLaser(int aux) {
  for (int j = col; j < 8; j++)
    lc.setLed(0, aux, j, true);
}
int timp;
int j;
void realShoot(int aux) {
  timp = millis();
   j = col + 1;
    lc.setLed(0, aux, j, true);
    if (millis() - timp >= 200) {
      timp=millis();
      j++;
      lc.setLed(0, aux, j - 1, false);
    }
  }
  


void shoot() {
  getShootPositions();
  
  
    if (man[i]) {

      //realShootLaser(i);
      realShoot(i);
      if ()
      man[i] -= 1;
      prevSwState = 1;
      Serial.println("DA");
    }
    i++;
if (i>=8)
i=0;

}

void loop() {
  // put your main code here, to run repeatedly:
  SwState = digitalRead(pinSW);
  //  animationStart(start);


  playerOneMove();

  shoot();
  //Serial.println(man[row]);
  //Serial.println(row);
  //  if (millis() - aux[] >= 200)
}
