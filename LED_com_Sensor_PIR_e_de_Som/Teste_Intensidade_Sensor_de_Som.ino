//Programa: Sensor de som KY-038
//Autor: Arduino e Cia

//Definicao pinos leds
int pinoled_ver = 3;
int pinoled_ama = 4;
int pinoled_verm = 5;

//Definicao pinos sensor
int pino_analogico = A5;
int pino_digital = 3;

int valor_A0 = 0;
int valor_D = 0;

void setup()
{
  Serial.begin(9600);
  //Define pinos led como saida
  pinMode(pinoled_ver, OUTPUT);
  pinMode(pinoled_ama, OUTPUT);
  pinMode(pinoled_verm, OUTPUT);
  //Define pinos sensor como entrada
  pinMode(pino_analogico, INPUT);
  pinMode(pino_digital, INPUT);
}

void loop()
{
  valor_A0 = analogRead(pino_analogico);
  valor_D = digitalRead(pino_digital);
  Serial.print("Saida A0: ");
  Serial.print(valor_A0);
  Serial.print(" Saida D0: ");
  Serial.println(valor_D);
  //Intensidade baixa
  if (valor_A0 > 20 && valor_A0 < 300)
  {
    digitalWrite(pinoled_ver, HIGH);
    digitalWrite(pinoled_ama, LOW);
    digitalWrite(pinoled_verm, LOW);
  }
  //Intensidade media
  if (valor_A0 > 301 && valor_A0 < 700)
  {
    digitalWrite(pinoled_ver, HIGH);
    digitalWrite(pinoled_ama, HIGH);
    digitalWrite(pinoled_verm, LOW);
  }
  //Intensidade alta
  if (valor_A0 > 701)
  {
    digitalWrite(pinoled_ver, HIGH);
    digitalWrite(pinoled_ama, HIGH);
    digitalWrite(pinoled_verm, HIGH);
  }
  delay(50);
  //Apaga todos os leds
  digitalWrite(pinoled_ver, LOW);
  digitalWrite(pinoled_ama, LOW);
  digitalWrite(pinoled_verm, LOW);
}
