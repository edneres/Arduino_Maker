// DEFINIÇÕES //
#define DHT11Pin  11    // Pino Sinal (Sensor DHT11)

// BIBLIOTECAS //
#include <Wire.h>
#include <MicroLCD.h>
#include <Adafruit_Sensor.h>         
#include <DHT.h>
#include <DHT_U.h>

// VARIÁVEIS //
uint32_t delayMS;   // Variável para atraso no tempo (DHT11) 

// OBJETOS //
LCD_SSD1306 display;                          // Para módulo contralado pelo CI SSD1306 OLED
DHT_Unified dht11(DHT11Pin, DHT11);           // Configurando o Sensor DHT (pino, tipo)
sensor_t sensor;

void setup() 
{
  display.begin();
  display.clear();

  dht11.begin();    // Inicializa o Sensor
}

void loop() 
{
  dht11.humidity().getSensor(&sensor);      // Mostra os detalhes do Sensor DHT11
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

  delayMS = sensor.min_delay / 1000;              // Define o atraso entre as leituras

  display.setFontSize(FONT_SIZE_MEDIUM);
  display.setCursor(35, 0);
  display.println("DADOS");

  while(1)
  {
    sensors_event_t event;                        // Inicializa o evento "Temperatura"
   dht11.temperature().getEvent(&event);          // Faz a leitura da temperatura
      
    if (isnan(event.temperature))                 // Se houver algum erro na leitura...
    {
      display.println("Erro na leitura da Temperatura!");
    }
      
    else                                          // Senão...
    {
      display.setFontSize(FONT_SIZE_SMALL);
      display.setCursor(0, 3);
      display.print("Temperatura: ");          
      display.print(event.temperature);           // Imprime a Temperatura
      display.println(" *C");
    }
      
    dht11.humidity().getEvent(&event);            // Faz a leitura de umidade
     
    if (isnan(event.relative_humidity))           // Se houver algum erro na leitura...
    {
      display.println("Erro na leitura da Umidade!");
    }
      
    else                                          // Senão...
    {
      display.setFontSize(FONT_SIZE_SMALL);
      display.setCursor(0, 4);
      display.print("Umidade:     ");            
      display.print(event.relative_humidity);     // Imprime a Umidade
      display.println(" %");
    }

    delay(delayMS);                               // Atraso entre as medições 
  }
}
