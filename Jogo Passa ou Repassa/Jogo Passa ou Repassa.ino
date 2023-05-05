//////////////
// EDIVÂNIA //
//   UFPI   //
//   2022   //
//////////////

int b1 = 7, b2 = 4, b3_reset = 2;
int e1 = 0, e2 = 0, e3 = 0;
int led1 = 13, led2 = 8;
int flag = 0; // flag == 1 >> ninguém pode mais apertar o botão >> Trava

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3_reset, INPUT);
}

void loop()
{
  e1 = digitalRead(b1);
  e2 = digitalRead(b2);
  e3 = digitalRead(b3_reset);
  
  if ( e1 == 1 && flag == 0)
  {
  	digitalWrite(led1, HIGH);
    flag = 1;
  }
  
  if ( e2 == 1 && flag == 0)
  {
  	digitalWrite(led2, HIGH);
    flag = 1;
  }
  
  if (e3 == 1 && flag == 1)
  {
  	flag = 0;
    digitalWrite(led1, 0);
    digitalWrite(led2, 0);
  }
}