                 //R1 R2  R3 R4 R5 R6 R7  R8  - cathodes
const int row[] = {6, 11, A5, 9, 5, A4, 4, A2};

                 //C1 C2 C3 C4  C5 C6  C7  C8 - anodes
const int col[] = {10, 3, 2, 7, A3, 8, 12, 13};

const int maxNum=8;
void setup() {
  // put your setup code here, to run once:
  for (int i=0;i<maxNum;i++)
  {
    pinMode(row[i],OUTPUT);
    pinMode(col[i],OUTPUT);
    }
}
// ca sa fie aprins trb sa fie row pe low , col high si ca sa fie off trb invers
void loop() {
  // put your main code here, to run repeatedly:

  for (int i=0;i<maxNum;i++)
  {
  
    digitalWrite(row[i],HIGH);
    digitalWrite(col[i],LOW);
    
    }


 /*
  for (int i=0;i<maxNum;i++)
  {
        for (int j=0;j<maxNum;j++)
    digitalWrite(col[j],LOW);
    for (int j=0;j<maxNum;j++)
    {digitalWrite(row[i],LOW);
    digitalWrite(col[j],HIGH);
    delay(100);
    }
    for (int j=0;j<maxNum;j++)
    digitalWrite(col[j],LOW);
    }
*/
digitalWrite(row[1],LOW);
digitalWrite(row[2],LOW);
digitalWrite(row[3],LOW);
digitalWrite(col[2],HIGH);
digitalWrite(col[5],HIGH);

/*

digitalWrite(row[5],LOW);
digitalWrite(col[1],HIGH);
digitalWrite(col[7],HIGH);*/

  for (int i=0;i<maxNum;i++)
  {
  
    digitalWrite(row[i],HIGH);
    digitalWrite(col[i],LOW);
    
    }


digitalWrite(row[6],LOW);
digitalWrite(col[2],HIGH);
digitalWrite(col[3],HIGH);
digitalWrite(col[4],HIGH);
digitalWrite(col[5],HIGH);

  for (int i=0;i<maxNum;i++)
  {
  
    digitalWrite(row[i],HIGH);
    digitalWrite(col[i],LOW);
    
    }

digitalWrite(row[5],LOW);
digitalWrite(col[1],HIGH);
digitalWrite(col[6],HIGH);
  
}
