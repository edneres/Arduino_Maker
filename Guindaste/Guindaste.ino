#define Button  6

#include <Servo.h>

Servo servo_base;   // Eixo 'x'
Servo servo_haste;  // Eixo 'y'

int eixo_x = 90;  // Servo da Base  ; Pino A0
int eixo_y = 90;  // Servo da Haste ; Pino A1

void setup() 
{
  servo_base.attach(3);
  servo_haste.attach(4);
  servo_base.write(90);
  servo_haste.write(90);

  pinMode(Button, INPUT_PULLUP);
}

void loop() 
{
  // Servo da Base //
  if((analogRead(A0) < 200) && (eixo_x < 180))
  {
    eixo_x++;
    servo_base.write(eixo_x);
  }

  if((analogRead(A0) > 700) && (eixo_x > 0))
  {
    eixo_x--;
    servo_base.write(eixo_x);
  }

  // Servo da Haste //
  if((analogRead(A1) < 200) && (eixo_y < 180))
  {
    eixo_y++;
    servo_haste.write(eixo_y);
  }

  if((analogRead(A1) > 700) && (eixo_y > 0))
  {
    eixo_y--;
    servo_haste.write(eixo_y);
  }

  // Botão //
  if(digitalRead(Button) != 1)
  {
    servo_base.write(90);
    servo_haste.write(90);
  }

  delay(15);
}