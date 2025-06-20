// Projeto TCC sem multiplexador
// Atividade Fácil - Página 3 com botões diretos

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões diretos (nota, certo, errado)
const int botaoNota = 2;
const int botaoCorreto = 3;
const int botaoErrado = 7;

// LEDs
const int ledVerde = 5;
const int ledVermelho = 6;

bool estadoAnterior[3] = {false, false, false};
unsigned long ultimoAcionamento[3] = {0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;

void setup() {
  // Botões
  pinMode(botaoNota, INPUT_PULLUP);
  pinMode(botaoCorreto, INPUT_PULLUP);
  pinMode(botaoErrado, INPUT_PULLUP);

  // LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);

  // DFPlayer
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Iniciando DFPlayer Mini...");

  if (!mp3.begin(mySerial)) {
    Serial.println("Erro ao iniciar o DFPlayer. Verifique conexões e SD.");
    while (true);
  }

  mp3.volume(25);
  Serial.println("DFPlayer iniciado com sucesso!");
}

void loop() {

  verificarBotao(0, botaoNota);
  verificarBotao(1, botaoCorreto);
  verificarBotao(2, botaoErrado);
}

void verificarBotao(int indice, int pino) {
  bool estadoAtual = digitalRead(pino) == LOW;
  unsigned long agora = millis();

  if (estadoAtual && !estadoAnterior[indice] && (agora - ultimoAcionamento[indice] > debounceDelay) && !audioTocando) {
    ultimoAcionamento[indice] = agora;
    Serial.print("Botão acionado no pino: ");
    Serial.println(pino);
    audioTocando = true;

    switch (indice) {
      case 0:
        mp3.playMp3Folder(6); // Dez reais
        delay(1000);
        break;
      case 1:
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(1); // Parabéns
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
      case 2:
        digitalWrite(ledVermelho, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho, LOW);
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}
