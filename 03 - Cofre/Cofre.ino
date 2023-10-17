#define PIN   3           // LED verde e Buzzer alegre
//#define RELE  2

#define linhas  4         // Número de linhas  do teclado
#define colunas 4         // Número de colunas do teclado

#define endereco    0x27  // Definir endereço no tinker
#define colunas_d   16    // Número de colunas do DISPLAY
#define linhas_d    2     // Número de linhas  do DISPLAY

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// MAPA DE TECLAS //
char mapa_teclas[linhas][colunas] = 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// PINAGEM KEYPAD//
byte linhas_pin[linhas]   = {12,11,10,9};  // Linhas de 0 à 3
byte colunas_pin[colunas] = {8,7,6,5};     // Colunas de 0 à 3


// CLASSE/OBJETO //
Keypad Teclado = Keypad(makeKeymap(mapa_teclas), linhas_pin, colunas_pin, linhas, colunas); 
Servo Servo_Trava;
LiquidCrystal_I2C lcd(endereco, colunas, linhas); // ver se não precisa alterar para colunas_d e linhas_d


// OUTRAS VARIÁVEIS //
char DIG_1 = '9';         // Definição da senha
char DIG_2 = 'C';
char tecla_pressionada1;  // Dígito 1 (dezena)
char tecla_pressionada2;  // Dígito 2 (unidade)
char tecla_pressionada3;  // Inicia a verificação
int  tentativas = 3;
int  ver;                 // Guarda o valor de retorno da função "verificacao"


// FUNÇÕES //
char digito1();
char digito2();
char start();
int verificacao(char tecla_pressionada1, char tecla_pressionada2, char DIG_1, char DIG_2);

void setup()
{
  pinMode(PIN, OUTPUT);
  //pinMode(RELE, OUTPUT);
  Servo_Trava.attach(4);         // Servo no Pino 4
  delay(10);
  Servo_Trava.write(90);

  lcd.init(); 		               // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight();	             // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear();		               // LIMPA O DISPLAY
  //Teclado.setDebounceTime(5);    // Tempo de atraso para leitura das teclas (realmente necessário???)

  lcd.print("   Bem vind@");
  delay(1000); 
  lcd.setCursor(0, 1); 	         // POSICIONA O CURSOR NA PRIMEIRA COLUNA DA LINHA 2
  lcd.print("    Ao Cofre");
  delay(3000); 
  lcd.clear(); 		               // LIMPA O DISPLAY
  delay(1000);
}

void loop()
{
  Senha: 
    lcd.print("   - Senha -");
    tecla_pressionada1 = digito1();
    lcd.setCursor(6, 1);
    lcd.print(tecla_pressionada1);

    tecla_pressionada2 = digito2();
    lcd.setCursor(7, 1);
    lcd.print(tecla_pressionada2);

    tecla_pressionada3 = start();
  
  if(tecla_pressionada3 == '#')   // Usuário quer testar a senha colocada
  {
    ver = verificacao(tecla_pressionada1, tecla_pressionada2, DIG_1, DIG_2);

    if(ver == 1)
    {
      lcd.clear();
      lcd.print("Acesso Liberado!");

      Servo_Trava.write(0);

      /*
      digitalWrite(PIN, HIGH);
      digitalWrite(RELE, HIGH);  // Aciona a trava >> Sistema destravado
      delay(2000);
      digitalWrite(PIN, LOW);
      digitalWrite(RELE, LOW);

      delay(1000);
      */

      tecla_pressionada1 = digito1();
      tecla_pressionada2 = digito2();
      
      while(tecla_pressionada1 != '#' && tecla_pressionada2 != '#')
      {
        tecla_pressionada1 = digito1();
        lcd.setCursor(6, 1);
        lcd.print(tecla_pressionada1);

        tecla_pressionada2 = digito2();
        lcd.setCursor(7, 1);
        lcd.print(tecla_pressionada2);
      }

      Servo_Trava.write(90);
    }

    else
    {
      tentativas--;

      if(tentativas == 0)    // Bloqueio do Sistema
      {
        lcd.clear();
        lcd.print("  Bloqueio do  ");
        lcd.setCursor(0, 1); 
        lcd.print("    Sistema    ");
        delay(1500);
        lcd.clear();
        lcd.noBacklight();
        
        exit(0);
      }

      lcd.clear();
      lcd.print("Acesso Negado!");
      lcd.setCursor(0, 1); 
      lcd.print("Tentativas: ");
      lcd.print(tentativas);
      delay(1500);
      lcd.clear();

      goto Senha;

      delay(1000);
    }
  }

  if(tecla_pressionada3 == '*')   // Usuário quer apagar a senha atual e colocar outra
  {
    lcd.clear();
    goto Senha;
  }

  lcd.clear();
  goto Senha;
}


char digito1()
{
  char tecla_pressionada = Teclado.getKey();
  while(tecla_pressionada == NO_KEY)
  {
    lcd.setCursor(6, 1); 
    lcd.print("_");
    lcd.setCursor(7, 1); 
    lcd.print("_");

    tecla_pressionada = Teclado.getKey();
  }

  return tecla_pressionada;
};

char digito2()
{
  char tecla_pressionada_ = Teclado.getKey();
  while(tecla_pressionada_ == NO_KEY)
  {
    lcd.setCursor(7, 1); 
    lcd.print("_");

    tecla_pressionada_ = Teclado.getKey();
  }

  return tecla_pressionada_;
};

char start()
{
  char tecla_pressionada__ = Teclado.getKey();
  while(tecla_pressionada__ == NO_KEY)
  {
    tecla_pressionada__ = Teclado.getKey();
  }

  return tecla_pressionada__;
};

int verificacao(char tecla_pressionada1, char tecla_pressionada2, char DIG_1, char DIG_2)
{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("  Verificando");

  for(int i = 0; i < 16; i++)
  {
    lcd.setCursor(i, 1);
    lcd.print("*");
    delay(100);
    lcd.setCursor(i, 1);
  }  

  lcd.clear();

  if(tecla_pressionada1 == DIG_1 && tecla_pressionada2 == DIG_2)
  {
    return 1;
  }

  else
  {
    return 0;
  }
};