// DEFINIÇÕES //
#define LED            2      // Led e Buzzer
#define Bot_L          7      // Botão para a esquerda
#define Bot_S          6      // Botão seletor
#define Bot_R          5      // Botão para a direita
#define Bip_Curto      200    // Ponto
#define Bip_Longo      600    // Linha
#define Espera_Entre   1000   // Espera entre um símbolo e outro
#define endereco       0x27   // Definir endereço no tinker (Endereço do Display)
#define colunas        16     // Número de colunas do DISPLAY
#define linhas         2      // Número de linhas  do DISPLAY


// BIBLIOTECAS //
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// INSTANCIANDO OBJETOS //
LiquidCrystal_I2C display(endereco, colunas, linhas);


// VETORES E MATRIZES //
char ligaLed[2] = {'.', '-'};

char alfabeto[37] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                     'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                     'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                     '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '
};
                    
char morse[37][7] = {{ ".- "}, {"-... "}, {"-.-. "}, {"-.. "}, {". "}, {"..-. "},
                    {"--. "}, { ".... "}, {".. " }, {".--- "}, {"-.- "}, {".-.. "},
                    {"-- "}, {"-. "}, {"--- "}, { ".--. "}, {"--.- "}, { ".-. "},
                    {"... "}, {"- "}, {"..- "}, {"...- "}, {".-- "}, {"-..- "},
                    {"-.-- "}, {"--.. "}, {".---- "}, {"--..- "}, {"...-- "},
                    {"....- "}, {"..... "}, {"-.... "}, {"--... "}, {"---.. "},
                    {"----. "}, {"----- "}, {" "}
};


// VARIÁVEIS //
String frase;
int estado_Bot_L = 0, estado_Bot_S = 0, estado_Bot_R = 0, opcao_menu = 1;


// DECLARAÇÃO DAS FUNÇÕES //
int    MENU(void);
String recebe_frase(void);
void   codifica_frase(String frase);
void   opcao_1(void);   // Codificador
void   opcao_2(void);   // Game


void setup() 
{
  pinMode(LED,  OUTPUT);
  pinMode(Bot_L, INPUT);
  pinMode(Bot_S, INPUT);
  pinMode(Bot_R, INPUT);

  randomSeed(analogRead(0));         // Irá fazer gerar um número aleatório em cada execução

  display.init(); 		               // INICIA A COMUNICAÇÃO COM O DISPLAY
  display.clear();		               // LIMPA O DISPLAY
  display.backlight();	             // LIGA A ILUMINAÇÃO DO DISPLAY
  delay(200);
  display.setCursor(3, 0);           // (coluna, linha)
  display.print("MORSE CODE");       // Printa no Display
  delay(200);
  display.setCursor(0, 1);           // (coluna, linha)
  display.print("-- --- .-. ... .");       // Printa no Display
  delay(2000);

  Serial.begin(9600);
}

void loop() 
{
  opcao_menu = MENU();

  switch(opcao_menu)
  {
    case 1:   // COMPLETO //
      display.setCursor(0, 0);           // (coluna, linha)
      display.print("PC tem que estar");  
      display.setCursor(3, 1);           
      display.print("conectado!");  
      delay(3000);
      display.noBacklight();
      display.clear();
      delay(200);
      opcao_1();
    break;

    case 2:
      opcao_2();
    break;
  }

  display.backlight();
  display.setCursor(0, 0);           // (coluna, linha)
  display.print("Voltando ao Menu");
  delay(2000);
}

// DESENVOLVIMENTO DAS FUNÇÕES //
int MENU(void)
{ 
  display.clear();		               // LIMPA O DISPLAY
  display.backlight();	             // LIGA A ILUMINAÇÃO DO DISPLAY
  int opcao = 1;                     // Variável de retorno da função

  while(digitalRead(Bot_S) != 1)     // Enquanto o botão de "select" não for pressionado...
  {
    // LEITURAS DOS ESTADOS DOS BOTÕES //
    estado_Bot_L = digitalRead(Bot_L);
    estado_Bot_S = digitalRead(Bot_S);  //
    estado_Bot_R = digitalRead(Bot_R);

    // CONFIGURAÇÃO DO "Bot_L" // 
    if(estado_Bot_L == 1)
    {
      digitalWrite(LED, 1);
      delay(50);
      digitalWrite(LED, 0); 

      opcao--;

      if(opcao == 0)
        opcao = 2;    
    }

    // CONFIGURAÇÃO DO "Bot_R" //
    if(estado_Bot_R == 1)
    {
      digitalWrite(LED, 1);
      delay(50);
      digitalWrite(LED, 0); 

      opcao ++;

      if(opcao == 3)
        opcao = 1;
    }

    display.clear();
    display.setCursor(6, 0);           // (coluna, linha)
    display.print("MODO");     

    if(opcao == 1)
    {
      display.setCursor(2, 1);           
      display.print(">Codificador"); 
    } 

    if(opcao == 2)
    {
      display.setCursor(5, 1);           
      display.print(">Game"); 
    }  

    delay(95);
  }

  // Quando o botão de "select" for pressionado...
  digitalWrite(LED, 1);

  if(opcao == 1)
  {
    display.setCursor(2, 0);           
    display.print(">Codificador");
  }

  if(opcao == 2)
  {
    display.setCursor(5, 0);           
    display.print(">Game");
  }

  display.setCursor(2, 1); 
  display.print("SELECIONADO!"); 
  delay(500);

  digitalWrite(LED, 0); 

  delay(1500);
  display.clear();
  display.noBacklight();
  delay(700);
  display.backlight();

  return opcao;  
}

String recebe_frase(void)   // Usado na opção 1
{
  String frase_recebida;    // Variável de retorno da função      

  while (Serial.available() == 0) 
  {
    // Sai apenas quando dados são recebidos
  }

  frase_recebida = Serial.readString();   // lê do buffer o dado recebido
  
  return frase_recebida;
}

void codifica_frase(String frase)   // Usado na opção 1
{
  for (int i = 0; frase[i] != 0; i++) 
  {
    for (int j = 0; alfabeto[j] != 0; j++) 
    {
      if (frase[i] == alfabeto[j]) 
      {
        Serial.print(morse[j]);            // Printa no Monitor Serial

        display.backlight();
        display.setCursor(0, 0);           // (coluna, linha)
        display.print(alfabeto[j]);        // Printa no LCD
        display.setCursor(0, 1);           
        display.print(morse[j]);    

        for (int k = 0; morse[j][k] != 0; k++) 
        {
          if (morse[j][k] == ligaLed[0]) 
          {
            digitalWrite(LED, HIGH);
            delay(Bip_Curto);                       
            digitalWrite(LED, LOW);
            delay(Bip_Curto);                       
          }

          if (morse[j][k] == ligaLed[1]) 
          {
            digitalWrite(LED, HIGH);
            delay(Bip_Longo);
            digitalWrite(LED, LOW);
            delay(Bip_Curto);                        
          }
        }

        delay(Espera_Entre);
        display.clear();
      }
    }
  }
}

void opcao_1(void)
{
  display.backlight();               // Liga a luz de fundo do LCD
  display.setCursor(0, 0);           // (coluna, linha)
  display.print("Digite 3 frases");  
  display.setCursor(0, 1);           
  display.print("(Monitor Serial)");  
  delay(2000);
  display.clear();

  int cont = 3;

  while(cont > 0)
  {
    Serial.println("Frase a ser codificada:");
    frase = recebe_frase();   // Recebe o que foi digitado no Monitor Serial
    Serial.println(frase);    // Printa no monitor serial o que será codificado
    frase.toLowerCase();      // Coloca a frase toda em minúsculo para ficar mais fácil na hora de analisar os caracteres em separado

    Serial.println("Frase em Morse:");
    codifica_frase(frase);    // Responde com o codigo codificado
    display.noBacklight();
    delay(100);
    Serial.println();
    Serial.println();

    cont--;
  }
}

void codifica_codigo(String codigo)   // Usado na opção 2
{
  for (int i = 0; codigo[i] != 0; i++) 
  {
    for (int j = 0; alfabeto[j] != 0; j++) 
    {
      if (codigo[i] == alfabeto[j]) 
      {
        display.backlight();
        display.setCursor(0, 0);           
        display.print(morse[j]);    

        for (int k = 0; morse[j][k] != 0; k++) 
        {
          if (morse[j][k] == ligaLed[0]) 
          {
            digitalWrite(LED, HIGH);
            delay(Bip_Curto);                       
            digitalWrite(LED, LOW);
            delay(Bip_Curto);                       
          }

          if (morse[j][k] == ligaLed[1]) 
          {
            digitalWrite(LED, HIGH);
            delay(Bip_Longo);
            digitalWrite(LED, LOW);
            delay(Bip_Curto);                        
          }
        }
      }
    }
  }
}

void opcao_2(void)
{
  int i, cont = 5;
  String caractere; 

  display.backlight();
  delay(100);

  while(cont != 0)
  {
    i = random(0, 36);      // (não pega o último que é " ") Sorteia um número aleatório para "i"

    caractere = alfabeto[i];
    codifica_codigo(caractere);   

    int j = 0;    // Variável a ser usada para passar ou voltar as opções disponíveis no alfabeto
    int trava = 0;

    while(trava == 0)   // Tem-se 3 chances para acertar qual é o símbolo que representa o código morse mostrado no Display 
    {
      while(digitalRead(Bot_S) != 1)  //Enquanto o "select" não é pressionado...
      {
        display.setCursor(0, 1);           
        display.print(alfabeto[j]); // Pinta o "a" no Display

        // LEITURAS DOS ESTADOS DOS BOTÕES //
        estado_Bot_L = digitalRead(Bot_L);
        estado_Bot_R = digitalRead(Bot_R);

        // CONFIGURAÇÃO DO "Bot_L" // 
        if(estado_Bot_L == 1)
        {
          digitalWrite(LED, 1);
          delay(50);
          digitalWrite(LED, 0); 

          j--;

          if(j == -1)
            j = 35; 

          display.setCursor(0, 1);           
          display.print(alfabeto[j]);    
        }

        // CONFIGURAÇÃO DO "Bot_R" //
        if(estado_Bot_R == 1)
        {
          digitalWrite(LED, 1);
          delay(50);//
          digitalWrite(LED, 0); 

          j++;

          if(j == 36)
            j = 0;

          display.setCursor(0, 1);           
          display.print(alfabeto[j]); 
        }

        delay(95);
      }

      // Quando o "select" é pressionado //
      if(alfabeto[j] == alfabeto[i])  // Se o símbolo selecionado for igual ao sorteado...
      {
        display.clear();
        display.setCursor(0, 0);           
        display.print("Certo!"); 
        delay(1000);
        display.clear();

        trava = 1;    // Para sair do loop (OK!)
      }

      else  // OK! //
      {
        display.clear();
        display.setCursor(0, 0);           
        display.print("Era o:"); 
        delay(200);
        display.setCursor(0, 1); 
        display.print(alfabeto[i]); 
        delay(2500);
        display.clear();
        display.noBacklight();
        delay(400);

        trava = 1;
      }
    }

    cont--;
  }
}



