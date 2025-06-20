// Projeto TCC
// Atividade Difícil - Página 3 com 5 botões e 2 LEDs

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões
const int botaoSanduiche = 2;
const int botaoSuco = 3;
const int botaoPicole = 4;
const int botaoRespostaErrada = 5;
const int botaoRespostaCerta = 6;

// LEDs
const int ledVerde = 7;
const int ledVermelho = 8;

bool estadoAnterior[5] = {false, false, false, false, false};
unsigned long ultimoAcionamento[5] = {0, 0, 0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;

void setup() {
  pinMode(botaoSanduiche, INPUT_PULLUP);
  pinMode(botaoSuco, INPUT_PULLUP);
  pinMode(botaoPicole, INPUT_PULLUP);
  pinMode(botaoRespostaErrada, INPUT_PULLUP);
  pinMode(botaoRespostaCerta, INPUT_PULLUP);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);

  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Iniciando DFPlayer Mini...");

  if (!mp3.begin(mySerial)) {
    Serial.println("Erro ao iniciar o DFPlayer. Verifique conexões e SD.");
    while (true);
  }

  mp3.volume(15);
  Serial.println("DFPlayer iniciado com sucesso!");
}

void loop() {
  verificarBotao(0, botaoSanduiche);
  verificarBotao(1, botaoSuco);
  verificarBotao(2, botaoPicole);
  verificarBotao(3, botaoRespostaErrada);
  verificarBotao(4, botaoRespostaCerta);
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
        mp3.playMp3Folder(17); // Sanduíche por 10 reais
        delay(1500);
        break;
      case 1:
        mp3.playMp3Folder(19); // Suco por 5 reais
        delay(1500);
        break;
      case 2:
        mp3.playMp3Folder(18); // Picolé por 2 reais
        delay(1500);
        break;
      case 3:
        digitalWrite(ledVermelho, HIGH);
        mp3.playMp3Folder(15); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho, LOW);
        break;
      case 4:
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(14); // Parabéns (voz do menino)
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}
