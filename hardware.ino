#define LED_PIN 8
#define BUTTON_PIN 13

#define PIN_POTENTIOMETER 0
#define PIN_RED 7 // pino LED Vermelho (R)
#define PIN_BLUE 5 // pino LED Verde (G)
#define PIN_GREEN 6 // Pino LED Azul (B)
#define PIN_LDR A1

bool lastButtonState = LOW;
bool ledState = LOW;

int led_R = 0;
int led_G = 0;
int led_B = 0;
int pot = 0; // Set POT value to default 0
int valorldr = 0;
int valorPot;
int colorRGB = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(PIN_POTENTIOMETER, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_LDR, INPUT);
  apagaLed();
  
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop()
{
  bool led = digitalRead(LED_PIN);
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      ledState = !ledState; // Alternar o estado do LED usando o operador de negação lógica
      digitalWrite(LED_PIN, ledState);
    }
  }

  // Receba o comando pela porta serial
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      ledState = LOW; // Define ledState como LOW (desligado)
      digitalWrite(LED_PIN, ledState);
    } else if (command == '2') {
      ledState = HIGH; // Define ledState como HIGH (ligado)
      digitalWrite(LED_PIN, ledState);
    } else if (command == '3') {
      // Envie o estado do LED pela porta serial
      Serial.println(ledState);
    } else if (command == '4') {
      // Mudar a cor do RGB
      acendeVermelho();
    } else if (command == '5') {
      acendeVerde();
    } else if (command == '6') {
      acendeAzul();
    } else if (command == '7') {
      Serial.println(colorRGB);
    } else if (command == '8') {
      delay(2000);
      valorPot = analogRead(pot); // lê o valor do potenciômetro (de 0 a 1023)
      if(valorPot >= 0 && valorPot <= 146) // menor que 256 apaga o LED
        {
          apagaLed();  
        }
        if(valorPot > 146 && valorPot <= 292) // entre 256 e 512, acende vermelho
        {
          acendeVermelho(); 
        }
        if(valorPot > 292 && valorPot <= 438) // entre 512 e 768, acende verde
        {
          acendeVerde();
        }
        if(valorPot > 438 && valorPot <= 584) // entre 768 e 1023, acende azul
        {
          acendeAzul();
        } 
        if(valorPot > 584 && valorPot <= 730) // entre 768 e 1023, acende azul
        {
          acendeAmarelo();
        } 
        if(valorPot > 730 && valorPot <= 876) // entre 768 e 1023, acende azul
        {
          acendeRosa();
        } 
        if(valorPot > 876 && valorPot <= 1023) // entre 768 e 1023, acende azul
        {
          acendeCiano();
        }        
    } else if (command == '9') {
      valorldr = analogRead(PIN_LDR);
      Serial.println(valorldr);
    }
  }  
}

void acendeVermelho()
{
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
  colorRGB = 1;
}

void acendeVerde()
{
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  colorRGB = 2;
}

void acendeAzul()
{
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  colorRGB = 3;
}

void apagaLed()
{
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, HIGH);
  colorRGB = 4;
}

void acendeAmarelo()
{
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  colorRGB = 5;
}

void acendeRosa()
{
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  colorRGB = 6;
}

void acendeCiano()
{
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, HIGH);
  colorRGB = 7;
}

bool readLed()
{
  bool ledState = digitalRead(LED_PIN);
  return ledState;
}
