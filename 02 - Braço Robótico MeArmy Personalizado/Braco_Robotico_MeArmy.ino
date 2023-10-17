///////////////////////////////////////////////////////////////////
// Acadêmica de Egenharia Elétrica Maria Edivânia Neres de Sousa //
// Universidade Federal do Piauí                                 //
// Teresina, Piauí. 10/08/2023                                   //
///////////////////////////////////////////////////////////////////

#include <Servo.h>

// Instanciação dos Servos
Servo Base, Garra, Profundidade, Altura;   

// Pinos Digitais dos Servo Motores
#define Pin_Base  5   
#define Pin_Garra 6   
#define Pin_Prof  9
#define Pin_Alt   8

// Pinos Analógicos dos Joysticks
#define Joy_Base  A0  // Eixo X
#define Joy_Garra A1  // Eixo Y
#define Joy_Prof  A4  // Eixo X'
#define Joy_Alt   A5  // EIxo Y'
 
int aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0;    
 
void setup()
{
  Base.attach(Pin_Base);
  Garra.attach(Pin_Garra);
  Profundidade.attach(Pin_Prof);
  Altura.attach(Pin_Alt);

  Serial.begin(9600);
}
 
void loop()
{
  // Servo da Base //
  if((analogRead(Joy_Base) < 200) && (aux1 < 180))
  {
    aux1++;

    if(aux1 == 180)
      aux1 = 180;

    Base.write(aux1);
  }

  if((analogRead(Joy_Base) > 700) && (aux1 > 0))
  {
    aux1--;

    if(aux1 == 0)
      aux1 = 0;

    Base.write(aux1);
  }

  // Servo da Garra //
  if((analogRead(Joy_Garra) < 200) && (aux2 < 180))
  {
    aux2++;

    if(aux2 == 180)
      aux2 = 180;

    Garra.write(aux2);
  }

  if((analogRead(Joy_Garra) > 700) && (aux2 > 0))
  {
    aux2--;

    if(aux2 == 0)
      aux2 = 0;

    Garra.write(aux2);
  }

  // Servo da Profundidade //
  if((analogRead(Joy_Prof) < 200) && (aux3 < 180))
  {
    aux3++;

    if(aux3 == 180)
      aux3 = 180;

    Profundidade.write(aux3);
  }

  if((analogRead(Joy_Prof) > 700) && (aux3 >= 0))
  {
    aux3--;

    if(aux3 == 0)
      aux3 = 0;
  }

  // Servo da Altura //
  if((analogRead(Joy_Alt) < 200) && (aux4 <= 180))
  {
    aux4++;

    if(aux4 == 180)
      aux4 = 180;

    Altura.write(aux4);
  }

  if((analogRead(Joy_Alt) > 700) && (aux4 >= 0))
  {
    aux4--;

    if(aux4 == 0)
      aux4 = 0;

    Altura.write(aux4);
  }

  delay(15);
}
