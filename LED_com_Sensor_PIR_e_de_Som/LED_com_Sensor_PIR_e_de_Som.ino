// DEFINIÇÕES //
#define tempoMaximoDeUmaPalma   150 //milisegundos
#define tempoMaximoEntrePalmas  500 //milisegundos

// VARIÁVEIS GLOBAIS//
const int pinoSom = 3; 
const int pinoPIR = 4; 
const int Botao = 8;
const int pinoLED = 9; 
const int Buzzer = 10;  // Ativo
int estadoPIR, estadoSom, estadoLED, estadoBot, Modo = 1; 
int  contaPalmas = 0;
long tempoEspera = 0;
long tempoEsperaEntrePalmas = 0;

void setup()
{
  pinMode(pinoLED, OUTPUT); 
  pinMode(Buzzer, OUTPUT);

  pinMode(Botao, INPUT);
  pinMode(pinoSom, INPUT);
  pinMode(pinoPIR, INPUT);  

  digitalWrite(pinoLED, 0); // Projeto começa com o LED apagado

  //Serial.begin(9600);
}

void loop()
{
  //Serial.println(digitalRead(pinoPIR));

  while(Modo == 1)   // Modo Sensor PIR (OK)
  {
    estadoBot = digitalRead(Botao);
    //Serial.print("Modo: ");
    //Serial.println(Modo);

    if(estadoBot == 1)
    {
      tone(Buzzer, 500);
      delay(300);
      noTone(Buzzer);

      Modo++; 
      //Modo = 2;
    }

    estadoPIR = digitalRead(pinoPIR);

    if(estadoPIR == 0)  // Se o sensor PIR detectar movimento...
    {
      digitalWrite(pinoLED, 1);
    }

    else
    {
      digitalWrite(pinoLED, 0);
    }
  }

  while(Modo == 2)  // Modo Sensor Som (OK)
  {
    estadoBot = digitalRead(Botao);
    //Serial.print("Modo: ");
    //Serial.println(Modo);

    if(estadoBot == 1)
    {
      tone(Buzzer, 500);
      delay(300);
      noTone(Buzzer);

      Modo--; 
      //Modo = 1;
    }

    int sensorSom = digitalRead(pinoSom);

    // Se o sensor detectou palmas
    if (sensorSom == LOW) 
    {
      //espera um tempo para nao detectar a mesma palma mais de uma vez 
      if (tempoEspera == 0) 
      {
          tempoEspera = tempoEsperaEntrePalmas = millis(); 
          contaPalmas++;
      } 
      
      else if ((millis() - tempoEspera) >= tempoMaximoDeUmaPalma) 
      {
          tempoEspera = 0;
      }
    }

    //caso exceda o tempo maximo entre palmas, zera o contador de palmas
    if ( (contaPalmas != 0) && ((millis() - tempoEsperaEntrePalmas) > 500) ) 
    {
      if(contaPalmas == 2)
      {
        digitalWrite(9, !digitalRead(9));
      }

      contaPalmas = 0;
      tempoEsperaEntrePalmas = millis();
    }
  }
}