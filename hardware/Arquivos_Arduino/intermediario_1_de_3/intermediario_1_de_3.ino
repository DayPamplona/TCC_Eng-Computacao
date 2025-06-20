// Projeto TCC sem multiplexador
// Atividade Intermediária - Página 1 com 6 botões e 3 LEDs

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

//Potenciômetro
const int pinoVolume = A0;

// Botões
const int botaoInstrucao = 2;
const int botaoNota5mais = 3;
const int botaoNota5igual = 4;
const int botaoRespostaCerta = 5;
const int botaoRespostaErrada1 = 6;
const int botaoRespostaErrada2 = 7;

// LEDs
const int ledVerde = 8;
const int ledVermelho1 = 9;
const int ledVermelho2 = 12;

bool estadoAnterior[6] = {false, false, false, false, false, false};
unsigned long ultimoAcionamento[6] = {0, 0, 0, 0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;

void setup() {
  // Botões
  pinMode(botaoInstrucao, INPUT_PULLUP);
  pinMode(botaoNota5mais, INPUT_PULLUP);
  pinMode(botaoNota5igual, INPUT_PULLUP);
  pinMode(botaoRespostaCerta, INPUT_PULLUP);
  pinMode(botaoRespostaErrada1, INPUT_PULLUP);
  pinMode(botaoRespostaErrada2, INPUT_PULLUP);

  // LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVermelho2, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho1, LOW);
  digitalWrite(ledVermelho2, LOW);

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

  verificarBotao(0, botaoInstrucao);
  verificarBotao(1, botaoNota5mais);
  verificarBotao(2, botaoNota5igual);
  verificarBotao(3, botaoRespostaCerta);
  verificarBotao(4, botaoRespostaErrada1);
  verificarBotao(5, botaoRespostaErrada2);
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
        mp3.playMp3Folder(7); // Instrução intermediária
        delay(2000);
        break;
      case 1:
        mp3.playMp3Folder(8); // Cinco reais... mais
        delay(1500);
        break;
      case 2:
        mp3.playMp3Folder(9); // Cinco reais... igual
        delay(1500);
        break;
      case 3:
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(1); // Parabéns
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
      case 4:
        digitalWrite(ledVermelho1, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho1, LOW);
        break;
      case 5:
        digitalWrite(ledVermelho2, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho2, LOW);
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}
