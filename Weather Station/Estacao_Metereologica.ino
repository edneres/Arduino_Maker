#define Botao_S        6      // Botão Seletor 
#define Botao          7      // Botão para passar
#define senChuvaPin    A0     
#define DHT11Pin       A1

#include <LiquidCrystal_I2C.h>
#include "dht.h"

LiquidCrystal_I2C display(0x27, 16, 2);
int opcao_menu;
dht DHT; 

int  MENU(void);
void chuva(void);
void DHT11sen(void);

void setup() 
{
  pinMode(Botao, INPUT_PULLUP);       // Botões ativados em nível lógico 0
  pinMode(Botao_S, INPUT_PULLUP);
  pinMode(senChuvaPin, INPUT);

  display.init(); 		                // INICIA A COMUNICAÇÃO COM O DISPLAY
  display.clear();		                // LIMPA O DISPLAY
  display.backlight();	              // LIGA A ILUMINAÇÃO DO DISPLAY
  delay(200);
  display.setCursor(0, 0);            // (coluna, linha)
  display.print("Weather  Station");  // Printa no Display
  delay(2000);
  display.clear();		               
  display.noBacklight();	           
  delay(200);
  display.backlight();
}

void loop()
{
  opcao_menu = MENU();

  if(opcao_menu == 1)
    chuva();

  if(opcao_menu == 2)
    DHT11sen();
}

int MENU(void)
{
  int opcao = 1;  // Variável de retorno da função

  while(digitalRead(Botao_S) != 0) // Enquanto o botão de "select" não for pressionado...
  {
    if(digitalRead(Botao) == 0)   //  Se o botão de passar for apertado...
    {
      opcao++; 

      if(opcao == 3)
        opcao = 1;
    }

    if(opcao == 1)
    {
      display.setCursor(5, 0);
      display.print("Chuva");  
    }

    if(opcao == 2)
    {
      display.setCursor(3, 0);
      display.print("Temperatura   ");  
      display.setCursor(4, 1);
      display.print("e Umidade    ");  
    } 

    delay(500);
    display.clear();
  }

  display.clear();
  return opcao;  
}

void chuva(void)
{
  int intensidade;     

  while(1)
  {
    intensidade = analogRead(senChuvaPin);
    
    if (intensidade > 1010 && intensidade < 1024)
    {
      display.setCursor(0, 0);  
      display.print("Sem Chuva");   
    }

    if (intensidade > 900 && intensidade < 1010)
    {
      display.setCursor(0, 0);  
      display.print("Chuva Leve"); 
    }
    
    if (intensidade > 400 && intensidade < 900) 
    {
      display.setCursor(0, 0);  
      display.print("Chuva Moderada"); 
    }

    if (intensidade > 0 && intensidade < 400)
    {
      display.setCursor(0, 0);  
      display.print("Chuva Forte");   
      display.setCursor(0, 1);  
      display.print("Alerta!");
    }

    delay(500);
    display.clear();
  }
}

void DHT11sen(void)
{
  while(1)
    {
      DHT.read11(DHT11Pin);
      display.setCursor(0, 0); 
      display.print("Temp: ");              
      display.print(DHT.temperature, 0);
      display.print("C");
      display.setCursor(0, 1);
      display.print("Umid: ");                  
      display.print(DHT.humidity);
      display.println("%    ");
      delay(100);   // Atraso entre as medições 
    }
}


















