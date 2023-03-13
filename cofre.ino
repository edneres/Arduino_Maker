// Código teste para liberação de acesso ao Cofre Arduino

#include <Password.h>   // Inclui biblioteca Password.h
#include <Keypad.h>       // Inclui biblioteca Keypa.h

#define rele 2              // Define o pino D2 como rele
#define buzzer 11           // Define o pino D11 como buzzer 

Password senha = Password("1234");      // Senha para liberação de acesso

const byte linha = 4;     // Define número de linhas
const byte coluna = 4;    // Define número de colunas

// Relaciona linha e colunas para determinação dos caracteres
char keys[linha][coluna] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinolinha[linha] = {10, 9, 8, 7};       // Declara os pinos de interpretação das linha
byte pinocoluna[coluna] = {6, 5, 4, 3};      // Declara os pinos de interpretação das coluna

Keypad keypad = Keypad(makeKeymap(keys), pinolinha, pinocoluna, linha, coluna);

void setup() {
  pinMode(rele, OUTPUT);             // Declara o pino como um pino de Saída de sinal
  pinMode(buzzer, OUTPUT);           // Declara o pino como um pino de Saída de sinal
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  keypad.setDebounceTime(5);         // Tempo de atraso para leitura das teclas.
}

void loop() {
  keypad.getKey();
}

// Realiza a leitura das teclas pressionadas e aguarda confirmação para verificar
void keypadEvent(KeypadEvent eKey) {
    switch (keypad.getState()) {
      case PRESSED:
        Serial.print("Digitado: ");
        Serial.println(eKey);
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        switch (eKey) {
          case 'C': verificasenha();
            break;
          default:
            senha.append(eKey);
        }
    }
  }

// Verifica o senha digitada após pressionar C
void verificasenha() {
  Serial.print("Verificando, aguarde... ");
  if (senha.evaluate()) {
    Serial.println("Acionando rele... ");
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(rele, HIGH);
    delay(2000);
    digitalWrite(rele, LOW);
    senha.reset();
  }
  else {
    digitalWrite(rele, LOW);
    Serial.println("Senha Invalida !");
    tone(buzzer, 500);
    delay(500);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 1500);
    delay(500);
    noTone(buzzer);
    delay(500);
    senha.reset();
  }
}
