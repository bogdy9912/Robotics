#include "LedControl.h" //  need the library
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

const int pinSW = 8;
const int pinX = A0;
const int pinY = A1;

const int pinSW2 = 4;
const int pinX2 = A2;
const int pinY2 = A3;

typedef struct projectile {
  int pozy;
  int pozx;
  double timp;
} projectile;

projectile man[8], man2[8];

int SwState;
int SwState2;
int prevSwState = 1;
int prevSwState2 = 1;
int xValue = 0;
int yValue = 0;
int xValue2 = 0;
int yValue2 = 0;
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
//int man[8];
int col = 1;
int row = 3;
int col2 = 7;
int row2;
bool matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int matrixType[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int ok = 0;
int oky = 0;
int ok2 = 0;
int oky2 = 0;
byte start = 0;
int aux[8];
/*
  void playerOneFormOn(int basePointX, int basePointY) {

  matrix[basePointX][basePointY] = 1;
  matrix[basePointX - 1][basePointY] = 1;
  matrix[basePointX + 1][basePointY] = 1;
  matrix[basePointX][basePointY + 1] = 1;
  lc.setLed(0, basePointX, basePointY, true);
  lc.setLed(0, basePointX - 1, basePointY, true);
  lc.setLed(0, basePointX + 1, basePointY, true);
  lc.setLed(0, basePointX, basePointY + 1, true);
  }
  void playerOneFormOff(int basePointX, int basePointY) {

  matrix[basePointX][basePointY] = 0;
  matrix[basePointX - 1][basePointY] = 0;
  matrix[basePointX + 1][basePointY] = 0;
  matrix[basePointX][basePointY + 1] = 0;
  lc.setLed(0, basePointX, basePointY, false);
  lc.setLed(0, basePointX - 1, basePointY, false);
  lc.setLed(0, basePointX + 1, basePointY, false);
  lc.setLed(0, basePointX, basePointY + 1, false);
  }*/
void  playerOneMove() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);


  if (xValue > thresholdMin && xValue < thresholdMax)
    ok = 0;

  if (xValue > thresholdMax && ok == 0)
  {
    if (row < 7)
    {
      /*      playerOneFormOff(row, col);
            row++;
            playerOneFormOn(row, col);*/
      matrix[row][col] = 0;
      matrixType[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      row++;
      matrix[row][col] = 1;
      matrixType[row][col] = 1;
      lc.setLed(0, row, col, matrix[row][col]);
      // turns off LED at col, row
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


// ------------------------------------------------------------------------

void  playerTwoMove() {
  xValue2 = analogRead(pinX2);
  yValue2 = analogRead(pinY2);


  if (xValue2 > thresholdMin && xValue2 < thresholdMax)
    ok2 = 0;

  if (xValue2 > thresholdMax && ok2 == 0)
  {
    if (row2 < 7)
    { matrix[row2][col2] = 0;
      matrixType[row2][col2] = 0;
      lc.setLed(0, row2, col2, matrix[row2][col2]);
      row2++;
      matrixType[row2][col2] = 1;
      matrix[row2][col2] = 1;
      lc.setLed(0, row2, col2, matrix[row2][col2]); // turns off LED at col, row
      ok2 = 1;
    }
  }
  else if (xValue2 < thresholdMin && ok2 == 0)
  {
    if (row2 > 0)
    {
      matrix[row2][col2] = 0;
      matrixType[row2][col2] = 0;
      lc.setLed(0, row2, col2, matrix[row2][col2]);
      row2--;
      matrixType[row2][col2] = 1;
      matrix[row2][col2] = 1;
      lc.setLed(0, row2, col2, matrix[row2][col2]); // turns off LED at col, row
      ok2 = 1;
    }
  }

  if (yValue2 > thresholdMin && yValue2 < thresholdMax)
    oky2 = 0;

  if (yValue2 > thresholdMax && oky2 == 0)
  {
    if (col2 < 7)
    {
      matrix[row2][col2] = 0;
      matrixType[row2][col2] = 0;
      lc.setLed(0, row2, col2, matrix[row2][col2]);
      col2++;
      matrixType[row2][col2] = 1;
      matrix[row2][col2] = 1;
      lc.setLed(0, row2, col2, matrix[row2][col2]); // turns off LED at col, row

      oky2 = 1;
    }
  }
  else if (yValue2 < thresholdMin && oky2 == 0)
  {
    if (col2 > 4)
    {
      matrix[row2][col2] = 0;
      matrixType[row2][col2] = 0;
      lc.setLed(0, row2, col2, matrix[row2][col2]);
      col2--;
      matrixType[row2][col2] = 1;
      matrix[row2][col2] = 1;
      lc.setLed(0, row2, col2, matrix[row2][col2]); // turns off LED at col, row
      oky2 = 1;
    }
  }

}
//--------------------------------------------------

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

void animationGameOver() {
  bool matrix[8][8] = {
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 1, 1}
  };
  { for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(0, row, col, matrix[row][col]);
      }
    }

  }
}
/*
  int shootFreq(int i) {
  if (millis() - aux[i] >= 2000) {
    {
      return 1;
      aux[i] = millis();
    }
  }
  }
*/

void getShootPositionsPlayerOne() {
  if (SwState == 0 && SwState != prevSwState)
  {

    prevSwState = SwState;
    if (man[row].pozx) {

    } else {
      man[row].pozx += 1;
      man[row].pozy = col + 1;
      man[row].timp  = millis();
    }
  }
}


//===============================
void getShootPositionsPlayerTwo() {
  if (SwState2 == 0 && SwState2 != prevSwState2)
  {
    prevSwState2 = SwState2;
    if (man2[row2].pozx) {

    } else {
      man2[row2].pozx += 1;
      man2[row2].pozy = col2 + 1;
      man2[row2].timp  = millis();
    }
  }
}

//===============================

void realShootLaserPlayerOne(int aux) {
  for (int j = col; j < 8; j++)
    lc.setLed(0, aux, j, true);
}

int timp;
int j;


void realShoot(int aux, projectile &ob) {
  matrix[aux][ob.pozy] = 1;
  lc.setLed(0, aux, ob.pozy, matrix[aux][ob.pozy]);
  if (millis() - ob.timp >= 200) {
    ob.timp = millis();
    ob.pozy++;
    matrix[aux][ob.pozy - 1] = 0;
    lc.setLed(0, aux , ob.pozy - 1, matrix[aux][ob.pozy - 1]);
    if (hit(ob, aux))
      Serial.println("HIT");
  }
}

// ****************************************************************************************************


void realShoot2(int aux, projectile &ob) {
  matrix[aux][ob.pozy] = 1;
  lc.setLed(0, aux, ob.pozy, matrix[aux][ob.pozy]);
  if (millis() - ob.timp >= 200) {
    ob.timp = millis();
    ob.pozy--;
    matrix[aux][ob.pozy - 1] = 0;
    lc.setLed(0, aux , ob.pozy + 1, matrix[aux][ob.pozy + 1]);
    if (hit(ob, aux))
      Serial.println("HIT");
  }
}


//*****************************************************************************************************

void gameOver() {
  animationGameOver();
}


int hit(projectile &ob, int aux) {
  //  Serial.println(matrixType[aux][ob.pozy]);
  if (matrix[aux][ob.pozy]) {
    {

      if (matrixType[aux][ob.pozy] == 1)
        // if (ob.pozy == 7)
        gameOver();
      if (ob.pozy < 7) {
        //      Serial.println("DA");
        ob.pozx -= 1;
      }
      return 1;
    }
  }
  return 0;
}
void shoot() {
  getShootPositionsPlayerOne();
  //  getShootPositionsPlayerTwo();


  if (man[i].pozx) {

    //realShootLaserPlayerOne(i);
    realShoot(i, man[i]);

    if (man[i].pozy >= 8)
      man[i].pozx -= 1;
    prevSwState = 1;

    // Serial.println(i);
  }
  if (man2[i].pozx) {

    realShoot2(i, man2[i]); //?
    if (man2[i].pozy >= 8)
      man2[i].pozx -= 1;
    prevSwState2 = 1;


  }
  i++;
  if (i >= 8)
    i = 0;

}

void loop() {
  // put your main code here, to run repeatedly:
  //  if (GameOver == 0){}
  SwState = digitalRead(pinSW);
  SwState2 = digitalRead(pinSW2);

  Serial.println(SwState2);
  //  animationStart(start);
  //  playerOneFormOn(row, col);
  playerTwoMove();
  playerOneMove();
  matrix[3][7] = 1;
  lc.setLed(0, 3, 7, true);
  matrix[2][5] = 1;
  lc.setLed(0, 2, 5, true);
  shoot();
  // Serial.println(matrix[3][7]);
  //Serial.println(man[row]);
  //Serial.println(row);
  //  if (millis() - aux[] >= 200)
}
