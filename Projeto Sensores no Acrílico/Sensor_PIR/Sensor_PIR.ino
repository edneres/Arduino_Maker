// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>

// OBJETOS //
LCD_SSD1306 display;    // Para módulo contralado pelo CI SSD1306 OLED

// VARIÁVEIS //
const int pinoPIR = 4; 
int estadoPIR;

void setup() 
{
  display.begin();
  display.clear();

  pinMode(pinoPIR, INPUT);

  display.setCursor(25, 0);
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.println("SENSOR PIR");
}

void loop() 
{
  estadoPIR = digitalRead(pinoPIR);

    if(estadoPIR == 1)  // Se o sensor PIR detectar movimento...
    {
      display.setCursor(0, 3);
      display.setFontSize(FONT_SIZE_MEDIUM);
      display.println("   Movimento! ");
    }

    else
    {
      display.setCursor(0, 3);
      display.setFontSize(FONT_SIZE_MEDIUM);
      display.println(" Sem Movimento");
    }
}
