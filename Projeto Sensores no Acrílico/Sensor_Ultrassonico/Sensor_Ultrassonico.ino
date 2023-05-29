// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>
#include <Ultrasonic.h>

// VARIÁVEIS //
const int trigPin = 13, echoPin = 12;  // Pinos TRIG e ECHO do Sensor Ultrassônico 
double distancia;

// OBJETOS //
LCD_SSD1306 display;                          // Para módulo contralado pelo CI SSD1306 OLED
Ultrasonic ultrasonico(trigPin, echoPin);     // Configurando o Sensor Ultrassônico (pinoTRIG, tipoECHO)

void setup() 
{
  display.begin();
  display.clear();

  display.setCursor(35, 0);
  display.setFontSize(FONT_SIZE_MEDIUM);
  display.println("DISTANCIA");
}

void loop()
{
  // Lê a distância em centímetros
    distancia = ultrasonico.read();
    
    // Mostra a distância medida no Display OLED
    display.setFontSize(FONT_SIZE_MEDIUM);
    display.setCursor(15, 3);
    display.print(distancia);
    display.print(" cm      ");
    
    // Aguarda um breve período antes de fazer uma nova medição
    delay(50);
}