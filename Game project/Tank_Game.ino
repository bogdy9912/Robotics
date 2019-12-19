#include "LedControl.h" //  need the library
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER

const int pinSW = 8;
const int pinX = A0;
const int pinY = A1;

const int pinSW2 = 7;
const int pinX2 = A2;
const int pinY2 = A3;

class projectile {
  public:
    int pozy;
    int pozx;
    double timp;

};

projectile man[8], man2[8];

int GameOverVal;
int level = 3;
int SwState;
int SwState2;
int prevSwState = 1;
int prevSwState2 = 1;
int xValue = 0;
int yValue = 0;
int xValue2 = 0;
int yValue2 = 0;
int k = 1;

const int thresholdMin = 400;
const int thresholdMax = 700;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinSW2, INPUT_PULLUP);
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

bool matrixNULL[8][8] = {
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
  // Serial.println(xValue);


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
      matrixType[row][col] = 2;
      lc.setLed(0, row, col, matrix[row][col]);
      // turns off LED at col, row
      ok = 1;
      /* Serial.print("LEFT");
        Serial.println("row2");
        Serial.println(row2);
        Serial.println("col2");
        Serial.println(col2);
        Serial.println(ok2);
        Serial.println("xValue");
        Serial.println(xValue);
        Serial.println("yValue");
        Serial.println(yValue);
        Serial.println("thresholdMin");
        Serial.println(thresholdMin);
        Serial.println("thresholdMax");
        Serial.println(thresholdMax);*/
      afis();
    }
  }
  else if (xValue < thresholdMin && ok == 0)
  {
    if (row > 0)
    {
      matrix[row][col] = 0;
      matrixType[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      row--;
      matrix[row][col] = 1;
      matrixType[row][col] = 2;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row
      ok = 1;
      /*   Serial.print("LEFT");
         Serial.println("row2");
         Serial.println(row2);
         Serial.println("col2");
         Serial.println(col2);
         Serial.println(ok2);
         Serial.println("xValue");
         Serial.println(xValue);
         Serial.println("yValue");
         Serial.println(yValue);
         Serial.println("thresholdMin");
         Serial.println(thresholdMin);
         Serial.println("thresholdMax");
         Serial.println(thresholdMax);*/
      afis();
    }
  }

  if (yValue > thresholdMin && yValue < thresholdMax)
    oky = 0;

  if (yValue > thresholdMax && oky == 0)
  {
    if (col < 3)
    {
      matrix[row][col] = 0;
      matrixType[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      col++;
      matrix[row][col] = 1;
      matrixType[row][col] = 2;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row

      oky = 1;
      /*  Serial.print("LEFT");
        Serial.println("row2");
        Serial.println(row2);
        Serial.println("col2");
        Serial.println(col2);
        Serial.println(ok2);
        Serial.println("xValue");
        Serial.println(xValue);
        Serial.println("yValue");
        Serial.println(yValue);
        Serial.println("thresholdMin");
        Serial.println(thresholdMin);
        Serial.println("thresholdMax");
        Serial.println(thresholdMax);*/
      afis();
    }
  }
  else if (yValue < thresholdMin && oky == 0)
  {
    if (col > 0)
    {
      matrix[row][col] = 0;
      matrixType[row][col] = 0;
      lc.setLed(0, row, col, matrix[row][col]);
      col--;
      matrix[row][col] = 1;
      matrixType[row][col] = 2;
      lc.setLed(0, row, col, matrix[row][col]); // turns off LED at col, row
      oky = 1;
      /*
        Serial.print("LEFT");
        Serial.println("row2");
        Serial.println(row2);
        Serial.println("col2");
        Serial.println(col2);
        Serial.println(ok2);
        Serial.println("xValue");
        Serial.println(xValue);
        Serial.println("yValue");
        Serial.println(yValue);
        Serial.println("thresholdMin");
        Serial.println(thresholdMin);
        Serial.println("thresholdMax");
        Serial.println(thresholdMax);*/
      afis();
    }
  }

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
      /*
            Serial.print("LEFT");
            Serial.println("row2");
            Serial.println(row2);
            Serial.println("col2");
            Serial.println(col2);
            Serial.println(ok2);
            Serial.println("xValue");
            Serial.println(xValue2);
            Serial.println("yValue");
            Serial.println(yValue2);
            Serial.println("thresholdMin");
            Serial.println(thresholdMin);
            Serial.println("thresholdMax");
            Serial.println(thresholdMax);
            if (xValue2 > thresholdMax)
              Serial.println("DAP");*/
      afis();
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
      /* Serial.println("RIGHT");
        Serial.println("row2");
        Serial.println(row2);
        Serial.println("col2");
        Serial.println(col2);
        Serial.println(ok2);
        Serial.println("xValue");
        Serial.println(xValue2);
        Serial.println("yValue");
        Serial.println(yValue2);
        Serial.println("thresholdMin");
        Serial.println(thresholdMin);
        Serial.println("thresholdMax");
        Serial.println(thresholdMax);*/
      afis();
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
      /*
            Serial.println("DOWN");
            Serial.println("row2");
            Serial.println(row2);
            Serial.println("col2");
            Serial.println(col2);
            Serial.println(oky2);
            Serial.println("xValue");
            Serial.println(xValue2);
            Serial.println("yValue");
            Serial.println(yValue2);
            Serial.println("thresholdMin");
            Serial.println(thresholdMin);
            Serial.println("thresholdMax");
            Serial.println(thresholdMax);*/
    }
    afis();
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
      /*
            Serial.println("UP");
            Serial.println("row2");
            Serial.println(row2);
            Serial.println("col2");
            Serial.println(col2);
            Serial.println(oky2);
            Serial.println("xValue");
            Serial.println(xValue2);
            Serial.println("yValue");
            Serial.println(yValue2);
            Serial.println("thresholdMin");
            Serial.println(thresholdMin);
            Serial.println("thresholdMax");
            Serial.println(thresholdMax);*/
      afis();
    }
  }

}
//--------------------------------------------------

void setAnimationStart(bool matrice[8][8]) {
  if (start == 0)
  { for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(0, row, col, matrice[row][col]);
      }
    }
  }
}


void animationStart() {
  delay(500);
  bool matrixOne[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  bool matrixTwo[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  bool matrixZero[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  setAnimationStart(matrixTwo);
  delay(800);
  setAnimationStart(matrixOne);
  delay(800);
  setAnimationStart(matrixZero);
  delay(800);
  setAnimationStart(matrixNULL);
}
void animationGameOver() {


  setAnimationStart(matrixNULL);
  const bool GameOver1[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 1, 0, 1, 1, 0},
    {0, 0, 1, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  { for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
      {
        lc.setLed(0, row, col, GameOver1[row][col]);
      }
    }

  }
  GameOverVal = 1;
}

// 333333333333333333333333333333333333333333333333333333333333333333333333333333333333
void afis() {
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      Serial.print(matrixType[col][row]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
  Serial.println();
}

void animationGameOver2() {


  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      lc.setLed(0, row, col, matrixNULL[row][col]);
    }
  }
  const bool GameOver2[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      lc.setLed(0, row, col, GameOver2[row][col]);
    }
  }


  GameOverVal = 1;
}

//3333333333333333333333333333333333333333333333333333333333333333333333333333333333333


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
  if (SwState2 == 0 && SwState2 != prevSwState2 )
  {
    //  Serial.println("********************************");
    prevSwState2 = SwState2;
    if (man2[row2].pozx) {

    } else {
      man2[row2].pozx += 1;
      man2[row2].pozy = col2 - 1;
      man2[row2].timp  = millis();
    }
  }
}

//===============================
int checkBulletGhost = 0;
/*
  void reverseBullet(projectile &ob, int aux){
  if (checkBulletGhost == 0){
    projectile bulletGhost = ob;
    }
  ob.pozx -= 1;
  bulletGhost.pozy -= 1;
  if (bulletGhost <0)
  bulletGhost.pozx = 0;



  matrix[aux][ob.pozy] = 0;


  }*/
void realShootLaserPlayerOne(int aux) {
  for (int j = col; j < 8; j++)
    lc.setLed(0, aux, j, true);
}

int timp;
int j;


void realShoot(int aux, projectile &ob) {
  matrix[aux][ob.pozy] = 1;
  matrixType[aux][ob.pozy] = 10;
  lc.setLed(0, aux, ob.pozy, matrix[aux][ob.pozy]);
  if (millis() - ob.timp >= 200) {
    ob.timp = millis();
    ob.pozy++;
    matrix[aux][ob.pozy - 1] = 0;
    matrixType[aux][ob.pozy - 1] = 0;
    lc.setLed(0, aux , ob.pozy - 1, matrix[aux][ob.pozy - 1]);
    if (hit(ob, aux))
      // Serial.println("HIT");
    {}
  }
}

// ****************************************************************************************************


void realShoot2(int aux, projectile &ob) {
  matrix[aux][ob.pozy] = 1;
  matrixType[aux][ob.pozy] = 10;
  lc.setLed(0, aux, ob.pozy, matrix[aux][ob.pozy]);
  if (millis() - ob.timp >= 200) {
    ob.timp = millis();
    ob.pozy--;
    matrix[aux][ob.pozy + 1] = 0;
    matrixType[aux][ob.pozy + 1] = 0;
    lc.setLed(0, aux , ob.pozy + 1, matrix[aux][ob.pozy + 1]);
    if (hit(ob, aux))
    {}     // Serial.println("HIT");
  }
}


//*****************************************************************************************************

void gameOver() {
  animationGameOver();
}

void gameOver2() {
  animationGameOver2();
}

int hit(projectile &ob, int aux) {
  //  Serial.println(matrixType[aux][ob.pozy]);
  if (matrix[aux][ob.pozy]) {
    {

      if (matrixType[aux][ob.pozy] == 1)
        // if (ob.pozy == 7)
        gameOver();
      if (matrixType[aux][ob.pozy] == 2)
        gameOver2();
      if (ob.pozy < 7) {
        if (matrixType[aux][ob.pozy] == 3) {
          // ob.pozx -= 1;
          //Serial.println("BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
        }
        if (matrixType[aux][ob.pozy] == 10) {
          // ob.pozx -= 1;
          //Serial.println("BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
        }
        if (matrixType[aux][ob.pozy] == 4) {}

        //reverseBullet();

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
  getShootPositionsPlayerTwo();


  if (man[i].pozx) {

    //realShootLaserPlayerOne(i);
    realShoot(i, man[i]);

    if (man[i].pozy > 7)
      man[i].pozx -= 1;
    prevSwState = 1;

    // Serial.println(i);
  }
  if (man2[i].pozx) {

    realShoot2(i, man2[i]); //?
    if (man2[i].pozy < 0)
      man2[i].pozx -= 1;
    prevSwState2 = 1;


  }
  i++;
  if (i > 7)
    i = 0;

}
int move[5] = {0, 1, 2, 3, 4};
int val = 2;
int val2 = 5;

void randomVal() {
  val = random(1, 3);
  val2 = random(4, 6);
}
long long put;

void addObstacolGradOne() {
  if (move[0] < 8)
  { matrix[move[0]][val] = 1;
    matrixType[move[0]][val] = 3;
    matrix[move[0]][val2] = 1;
    matrixType[move[0]][val2] = 3;
    lc.setLed(0, move[0], val, true);
    lc.setLed(0, move[0], val2, true);
    if (millis() - put >= 400) {
      put = millis();
      move[0]++;
      matrix[move[0] - 1][val] = 0;
      matrixType[move[0] - 1][val] = 0;
      lc.setLed(0, move[0] - 1, val, false);

      matrix[move[0] - 1][val2] = 0;
      matrixType[move[0] - 1][val2] = 0;
      lc.setLed(0, move[0] - 1, val2 , false);
    }
  }
  else
  {
    if (millis() - put >= 3000) {
      put = millis();
      randomVal();
      move[0] = 0;
    }
  }
}



void addObstacolGradTwo() {
  if (move[1] < 8)
  { matrix[move[1]][val] = 1;
    matrix[move[1] - 1][val] = 1;
    matrixType[move[1]][val] = 3;
    matrixType[move[1] - 1][val] = 3;
    matrix[move[1]][val2] = 1;
    matrix[move[1] - 1][val2] = 1;
    matrixType[move[1]][val2] = 3;
    matrixType[move[1] - 1][val2] = 3;
    lc.setLed(0, move[1], val, true);
    lc.setLed(0, move[1] - 1, val , true);
    lc.setLed(0, move[1], val2, true);
    lc.setLed(0, move[1] - 1, val2, true);
    if (millis() - put >= 400) {
      put = millis();
      move[1]++;
      matrix[move[1] - 1][val] = 0;
      matrix[move[1] - 2][val] = 0;
      matrixType[move[1] - 1][val] = 0;
      matrixType[move[1] - 2][val] = 0;
      lc.setLed(0, move[1] - 1, val, false);
      lc.setLed(0, move[1] - 2, val, false);
      matrix[move[1] - 1][val2] = 0;
      matrix[move[1] - 2][val2] = 0;
      matrixType[move[1] - 1][val2] = 0;
      matrixType[move[1] - 2][val2] = 0;
      lc.setLed(0, move[1] - 1, val2 , false);
      lc.setLed(0, move[1] - 2, val2 , false);
    }
  }
  else
  {
    if (millis() - put >= 3000) {
      put = millis();
      randomVal();
      move[1] = 1;
    }
  }
}


void addObstacolGradThree() {
  if (move[1] < 8)
  { matrix[move[1]][val] = 1;
    matrix[move[1] - 1][val] = 1;
    matrixType[move[1]][val] = 4;
    matrixType[move[1] - 1][val] = 4;
    matrix[move[1]][val2] = 1;
    matrix[move[1] - 1][val2] = 1;
    matrixType[move[1]][val2] = 4;
    matrixType[move[1] - 1][val2] = 4;
    lc.setLed(0, move[1], val, true);
    lc.setLed(0, move[1] - 1, val , true);
    lc.setLed(0, move[1], val2, true);
    lc.setLed(0, move[1] - 1, val2, true);
    if (millis() - put >= 400) {
      put = millis();
      move[1]++;
      matrix[move[1] - 1][val] = 0;
      matrix[move[1] - 2][val] = 0;
      matrixType[move[1] - 1][val] = 0;
      matrixType[move[1] - 2][val] = 0;
      lc.setLed(0, move[1] - 1, val, false);
      lc.setLed(0, move[1] - 2, val, false);
      matrix[move[1] - 1][val2] = 0;
      matrix[move[1] - 2][val2] = 0;
      matrixType[move[1] - 1][val2] = 0;
      matrixType[move[1] - 2][val2] = 0;
      lc.setLed(0, move[1] - 1, val2 , false);
      lc.setLed(0, move[1] - 2, val2 , false);
    }
  }
  else
  {
    if (millis() - put >= 3000) {
      put = millis();
      randomVal();
      move[1] = 1;
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if (GameOverVal == 0) {
    SwState = digitalRead(pinSW);
    SwState2 = digitalRead(pinSW2);


    //  animationStart(start);
    //  playerOneFormOn(row, col);
    playerTwoMove();
    playerOneMove();
    /*
        matrix[3][7] = 1;
      lc.setLed(0, 3, 7, true);
      matrix[2][5] = 1;
      lc.setLed(0, 2, 5, true);
    */
    shoot();
    if (GameOverVal == 0)
    { if (level == 2) {

        addObstacolGradOne();

      }
      if (level == 3)
        addObstacolGradTwo();
      if (level == 4)
        addObstacolGradThree();
    }

  }
  else {

    xValue = analogRead(pinX);
    xValue2 = analogRead(pinX2);
    if (xValue < thresholdMin && xValue2 < thresholdMin )
    { GameOverVal = 0;

      animationStart();

    }



  }
  // Serial.println(matrix[3][7]);
  //Serial.println(man[row]);
  //Serial.println(row);
  //  if (millis() - aux[] >= 200)
}
