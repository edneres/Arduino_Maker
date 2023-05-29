// DEFINIÇÕES //
#define SensorPin         A0    // Pino analog. (Sensor de Umidade do Solo) 
#define analogSoloSeco    400   // Valor medido em teste com o solo seco 
#define analogSoloMolhado 150   // Valor medido em teste com o solo molhado 
#define percSoloSeco      0     // Menor percentual (0% >> solo seco >> NÃO ALTERAR)
#define percSoloMolhado   100   // Maior percentual (100% >> solo encharcado >> NÃO ALTERAR)

// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>

// VARIÁVEIS //
double umidade_percentual;  // Variável que armazena o percentual de umidade no solo  (pode ser delarada dentro da função)

// OBJETOS //
LCD_SSD1306 display;                          // Para módulo contralado pelo CI SSD1306 OLED

void setup() 
{
  display.begin();
  display.clear();
}

void loop() 
{
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.setCursor(35, 0);
  display.println("DADOS");
  display.setFontSize(FONT_SIZE_SMALL);
  display.setCursor(0, 3);

  umidade_percentual = constrain(analogRead(SensorPin),analogSoloMolhado,analogSoloSeco);                     //Mantém valor lido dentro do intervalo (entre "analogSoloMolhado" E "analogSoloSeco")
  umidade_percentual = map(umidade_percentual,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //Muda a variável "umidade_percentual" de escala
  display.print("Umidade do Solo: "); 
  display.print(umidade_percentual); 
  display.println("%"); 
  delay(1000);  
}
