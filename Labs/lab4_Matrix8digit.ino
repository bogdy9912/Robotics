const int aPin = 2;
const int bPin = 3;
const int cPin = 4;
const int dPin = 5;
const int ePin = 6;
const int fPin = 7;
const int gPin = 8;
const int dotPin = 9;
const int noOfDigits = 10;
const int sizeArr = 8;

byte stateDP = 0;

const byte Pin[sizeArr]= {aPin,bPin,cPin,dPin,ePin,fPin,gPin,dotPin};
const byte digitMatrix[noOfDigits][sizeArr - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
}; 

void displayFunction(int digit)
{
  
  for (int i=0;i<=sizeArr-1;i++)
    digitalWrite(Pin[i],digitMatrix[digit][i]);
  digitalWrite(Pin[sizeArr-1],stateDP);
}


void setup() {
  // put your setup code here, to run once:

  for (int i=0;i<sizeArr;i++)
    pinMode(Pin[i],OUTPUT);

}

int state = 0;
int index = 0;
void loop() {// put your main code here, to run repeatedly:

  displayFunction(index);
  delay (600);
  
  index++;
  //digitalWrite(Pin[index-1],0);

  if (index == noOfDigits)
  {
    stateDP = !stateDP;
    index = 0;
    }
  
}
