// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>

// OBJETOS //
LCD_SSD1306 display;      // Para módulo contralado pelo CI SSD1306 OLED

// VARIÁVEIS //
int pino_analogico = A5;
int pino_digital = 6;
int valor_A0 = 0;
int valor_D = 0;

void setup()
{
  pinMode(pino_analogico, INPUT);
  pinMode(pino_digital, INPUT);

  display.begin();
  display.clear();

  display.setCursor(15, 0);
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.println("INTENSIDADE SO SOM");

  Serial.begin(9600);
}

void loop()
{
  valor_A0 = analogRead(pino_analogico);
  valor_D = digitalRead(pino_digital);

  Serial.print("Saida A0: ");
  Serial.print(valor_A0);

  Serial.print(" Saida D0: ");
  Serial.println(valor_D);

  // Baixa Intensidade do Som
  if (valor_A0 > 20 && valor_A0 < 300)
  {
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(15, 3);
    display.print("Baixa: ");   // 7
    display.print(valor_A0);
    display.print("  ");
  }

  // Média Intensidade do Som
  if (valor_A0 > 301 && valor_A0 < 700)
  {
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(15, 3);
    display.print("Media: ");   // 7
    display.print(valor_A0);
    display.print("  ");
  }
  // Alta Intensidade do Som
  if (valor_A0 > 701)
  {
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(15, 3);
    display.print(" Alta: ");  // 6
    display.print(valor_A0);
    display.print("  ");
  }
  
  delay(100);
}
