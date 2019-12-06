                 //R1 R2  R3 R4 R5 R6 R7  R8  - cathodes
const int row[] = {6, 11, A5, 9, 5, A4, 4, A2};

                 //C1 C2 C3 C4  C5 C6  C7  C8 - anodes
const int col[] = {10, 3, 2, 7, A3, 8, 12, 13};

const int maxNum=8;
const int pinX=A1;
const int pinY=A0;
int thresholdMin=400;
int thresholdMax=600;
int x;
int y;
int ok1;
int xValue = 0;
int yValue = 0;

void setup() {
  // put your setup code here, to run once:

    for (int i=0;i<maxNum;i++)
  {
    pinMode(row[i],OUTPUT);
    pinMode(col[i],OUTPUT);
    }
    

}

int ok;
void loop() {
  // put your main code here, to run repeatedly:

xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  
  for (int i=0;i<maxNum;i++)
  {
  
    digitalWrite(row[i],HIGH);
    digitalWrite(col[i],LOW);
    
    }


    if (xValue >thresholdMin && xValue<thresholdMax)
    ok=0;
    
if (xValue>thresholdMax && ok ==0)
  {
    x++;
    ok=1;
  
  }
  else if(xValue < thresholdMin && ok == 0)
  {
    x--;
    ok=1;
    }

  

    if (yValue >thresholdMin && yValue<thresholdMax)
    ok1=0;
    
if (yValue>thresholdMax && ok1 ==0)
  {
    y--;
    ok1=1;
  
  }
  else if(yValue < thresholdMin && ok1 == 0)
  {
    y++;
    ok1=1;
    }
    if (x<0)
    x=7;
    if (x>7)
    x=0;

    if (y<0)
    y=7;
  if (y>7)
    y=0;

      digitalWrite(row[x],LOW);
  digitalWrite(col[y],HIGH);

  
  for (int i=0;i<maxNum;i++)
  {
  
    digitalWrite(row[i],HIGH);
    digitalWrite(col[i],LOW);
    
    }



}
