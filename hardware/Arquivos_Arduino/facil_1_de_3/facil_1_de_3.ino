// Projeto TCC sem multiplexador
// Atividade Fácil - Página 1 com botões diretos

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

//Potenciômetro
//const int pinoVolume = A0;

// Botões diretos
const int botaoInstrucao = 2;
const int botaoNota = 3;
const int botaoCorreto = 4;
const int botaoErrado = 5;

// LEDs
const int ledVerde = 6;
const int ledVermelho = 7;

bool estadoAnterior[4] = {false, false, false, false};
unsigned long ultimoAcionamento[4] = {0, 0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;
bool instrucoesAtivadas = false;

void setup() {
  // Botões
  pinMode(botaoInstrucao, INPUT_PULLUP);
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
  // Controle de volume via potenciômetro
  //int leituraVolume = analogRead(pinoVolume);
  //int volumeDF = map(leituraVolume, 0, 1023, 0, 30);
  //mp3.volume(volumeDF);

  verificarBotao(0, botaoInstrucao);
  verificarBotao(1, botaoNota);
  verificarBotao(2, botaoCorreto);
  verificarBotao(3, botaoErrado);
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
        mp3.playMp3Folder(3); // Instrução
        delay(2000);
        instrucoesAtivadas = true;
        break;
      case 1:
        if (instrucoesAtivadas) {
          mp3.playMp3Folder(4); // Dois reais
          delay(1000);
        }
        break;
      case 2:
        if (instrucoesAtivadas) {
          digitalWrite(ledVerde, HIGH);
          mp3.playMp3Folder(1); // Parabéns
          delay(1500);
          digitalWrite(ledVerde, LOW);
        }
        break;
      case 3:
        if (instrucoesAtivadas) {
          digitalWrite(ledVermelho, HIGH);
          mp3.playMp3Folder(2); // Tente novamente
          delay(1500);
          digitalWrite(ledVermelho, LOW);
        }
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}
