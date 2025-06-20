// Projeto TCC sem multiplexador
// Atividade Difícil - Página 1 com 6 botões e 3 LEDs

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões
const int botaoInstrucao = 2;
const int botaoSanduiche = 3;
const int botaoPicole = 4;
const int botaoRespostaErrada1 = 5;
const int botaoRespostaErrada2 = 6;
const int botaoRespostaCerta = 7;

// LEDs
const int ledVerde = 8;
const int ledVermelho1 = 9;
const int ledVermelho2 = 12;

bool estadoAnterior[6] = {false, false, false, false, false, false};
unsigned long ultimoAcionamento[6] = {0, 0, 0, 0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;

void setup() {
  pinMode(botaoInstrucao, INPUT_PULLUP);
  pinMode(botaoSanduiche, INPUT_PULLUP);
  pinMode(botaoPicole, INPUT_PULLUP);
  pinMode(botaoRespostaErrada1, INPUT_PULLUP);
  pinMode(botaoRespostaErrada2, INPUT_PULLUP);
  pinMode(botaoRespostaCerta, INPUT_PULLUP);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVermelho2, OUTPUT);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho1, LOW);
  digitalWrite(ledVermelho2, LOW);

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
  verificarBotao(1, botaoSanduiche);
  verificarBotao(2, botaoPicole);
  verificarBotao(3, botaoRespostaErrada1);
  verificarBotao(4, botaoRespostaErrada2);
  verificarBotao(5, botaoRespostaCerta);
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
        mp3.playMp3Folder(16); // Instrução: Oi, me ajuda a somar os lanches?
        delay(2000);
        break;
      case 1:
        mp3.playMp3Folder(17); // Sanduíche por 10 reais
        delay(1500);
        break;
      case 2:
        mp3.playMp3Folder(18); // Picolé por 2 reais
        delay(1500);
        break;
      case 3:
        digitalWrite(ledVermelho1, HIGH);
        mp3.playMp3Folder(15); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho1, LOW);
        break;
      case 4:
        digitalWrite(ledVermelho2, HIGH);
        mp3.playMp3Folder(15); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho2, LOW);
        break;
      case 5:
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
