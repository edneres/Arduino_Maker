// DEFINIÇÕES //
#define Bot_L 7  // Botão para a esquerda
#define Bot_S 6  // Botão seletor
#define Bot_R 5  // Botão para a direita

#define trigPin 13  // Pino TRIG (Sensor Ultrassônico)
#define echoPin 12  // Pino ECHO (Sensor Ultrassônico)

#define DHT11Pin  11                    // Pino Sinal (Sensor DHT11)

#define SensorPin         A0    // Pino analog. do sensor de umidade do solo 
#define analogSoloSeco    400   //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
#define analogSoloMolhado 150   //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
#define percSoloSeco      0     //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
#define percSoloMolhado   100   //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>

#include <Adafruit_Sensor.h>         
#include <DHT.h>
#include <DHT_U.h>

// OBJETOS //
LCD_SSD1306 display;                // Para módulo contralado pelo CI SSD1306 OLED
DHT_Unified dht(DHT11Pin, DHT11);   // Configurando o Sensor DHT (pino, tipo)
sensor_t sensor;

// VARIÁVEIS //
int estado_Bot_L = 0, estado_Bot_S = 0, estado_Bot_R = 0, opcao_menu = 1;
double distancia;   // Variável para guardar a distância (Ultrassônico)
uint32_t delayMS;   // Variável para atraso no tempo (DHT11)
double umidade_percentual;  // Variável que armazena o percentual de umidade no solo

// DECLARAÇÃO DE FUNÇÕES //
int menu(void);
void medirDistancia(void);
void medirUmidTemp(void);
void medirUmidSolo(void);

void setup() 
{
  display.begin();
  display.clear();

  pinMode(Bot_L, INPUT);
  pinMode(Bot_S, INPUT);
  pinMode(Bot_R, INPUT);

  pinMode(trigPin, OUTPUT);   // Configura o pino do trigger como saída
  pinMode(echoPin, INPUT);    // Configura o pino do echo como entrada

  dht.begin();                // inicializa a função
}

void loop() 
{
  opcao_menu = menu();

  switch(opcao_menu)
  {
    case 1:
      medirDistancia();
    break; 

    case 2:
      medirUmidTemp();
    break;

    case 3:
      medirUmidSolo();
    break;
  }
}


int menu(void) // OK //
{
  display.setCursor(35, 0);
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.println("SENSOR");

  int opcao = 1;  // Variável de retorno da função

  while (digitalRead(Bot_S) != 1)  // Enquanto o botão de "select" não for pressionado...
  {
    // LEITURAS DOS ESTADOS DOS BOTÕES //
    estado_Bot_L = digitalRead(Bot_L);
    estado_Bot_R = digitalRead(Bot_R);

    // CONFIGURAÇÃO DO "Bot_L" //
    if (estado_Bot_L == 1) 
    {
      opcao--;

      if (opcao == 0)  
        opcao = 3;
    }

    // CONFIGURAÇÃO DO "Bot_R" //
    if (estado_Bot_R == 1) 
    {
      opcao++;

      if (opcao == 4)
        opcao = 1;
    }

    if (opcao == 1) 
    {
      display.setCursor(10, 3);
      display.setFontSize(FONT_SIZE_MEDIUM);
      display.println("Ultrassonico   ");
      display.setCursor(11, 5);
      display.clearLine(5);
      display.clearLine(6);
      // desenhar um símbolo //
    }

    if (opcao == 2) 
    {
      display.setCursor(10, 3);
      display.setFontSize(FONT_SIZE_MEDIUM);
      display.println("  Umidade e    ");
      display.setCursor(10, 5);
      display.println(" Temperatura");
      // desenhar um símbolo //
    }

    if (opcao == 3) 
    {
      display.setCursor(10, 3);
      display.setFontSize(FONT_SIZE_MEDIUM);
      display.println("   Umidade    ");
      display.setCursor(10, 5);
      display.println("   do Solo      ");
      // desenhar um símbolo //
    }

    delay(95);  //95
  }

  // Quando o botão de "select" for pressionado... //
  display.clear(0, 0, 128, 64);   // Limpa todo o display

  if (opcao == 1) 
  {
    display.setCursor(12, 0);
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.println("Ultrassonico");
    // desenhar um símbolo //
  }


  if (opcao == 2) 
  {
    display.setCursor(5, 0);
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.println(" Umid. e Temp.");
    // desenhar um símbolo //
  }

  if (opcao == 3) 
  {
    display.setCursor(2, 0);
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.println(" Umid. do Solo");
    // desenhar um símbolo //
  }

  display.setCursor(15, 3);
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.println("SELECIONADO!");
  delay(1000);

  display.clear(0, 0, 128, 64);   // Limpa todo o display

  return opcao;
}

void medirDistancia(void) // Ok //
{
  while(1)
  {
    // Define a duração do pulso de trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Mede o tempo de duração do pulso de echo
    distancia = pulseIn(echoPin, HIGH);
    
    // Converte a duração do pulso em distância (cm)
    distancia = distancia / 58;
    
    // Mostra a distância medida no Display OLED
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(20, 0);
    display.println("Distancia");
    display.setCursor(15, 3);
    display.print(distancia);
    display.print(" cm      ");
    
    // Aguarda um breve período antes de fazer uma nova medição
    delay(100);
  }
}

void medirUmidTemp(void)  // OK //
{
  while(1)
  {
    dht.humidity().getSensor(&sensor);      // Mostra os detalhes do Sensor DHT
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(27, 0);
    display.println("DETALHES");
    display.setFontSize(FONT_SIZE_SMALL);
    display.setCursor(0, 2);
    display.println("---------------------");
    display.print  ("Sensor:       ");  display.println(sensor.name);
    display.print  ("Valor max:    ");  display.print(sensor.max_value);  display.println("%");
    display.print  ("Valor min:    ");  display.print(sensor.min_value);  display.println("%");
    display.print  ("Resolucao:     "); display.print(sensor.resolution); display.println("%");
    display.println("---------------------");
    delay(3000);
    display.clear(0, 0, 128, 64);   // Limpa todo o display

    delayMS = sensor.min_delay / 1000;            // define o atraso entre as leituras

    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(35, 0);
    display.println("DADOS");

    while(1)
    {
      sensors_event_t event;                        // inicializa o evento da Temperatura
      dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
      
      if (isnan(event.temperature))                 // se algum erro na leitura
      {
        display.println("Erro na leitura da Temperatura!");
      }
      
      else                                          // senão
      {
        display.setFontSize(FONT_SIZE_SMALL);
        display.setCursor(0, 3);
        display.print("Temperatura: ");              // imprime a Temperatura
        display.print(event.temperature);
        display.println(" *C");
      }
      
      dht.humidity().getEvent(&event);              // faz a leitura de umidade
      
      if (isnan(event.relative_humidity))           // se algum erro na leitura
      {
        display.println("Erro na leitura da Umidade!");
      }
      
      else                                          // senão
      {
        display.setFontSize(FONT_SIZE_SMALL);
        display.setCursor(0, 4);
        display.print("Umidade:     ");                  // imprime a Umidade
        display.print(event.relative_humidity);
        display.println(" %");
      }

      delay(delayMS);                               // atraso entre as medições 
    }
  }
}

void medirUmidSolo(void)
{
  while(1)
  {
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(35, 0);
    display.println("DADOS");
    display.setFontSize(FONT_SIZE_SMALL);
    display.setCursor(0, 3);

    umidade_percentual = constrain(analogRead(SensorPin),analogSoloMolhado,analogSoloSeco); //MANTÉM valorLido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
    umidade_percentual = map(umidade_percentual,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
    display.print("Umidade do Solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    display.print(umidade_percentual); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
    display.println("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
    delay(1000);  //INTERVALO DE 1 SEGUNDO
  }
}