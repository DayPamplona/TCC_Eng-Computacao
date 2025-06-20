// Projeto TCC sem multiplexador
// Atividade Fácil - Página 2 com botões diretos e pinos sequenciais

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Potenciômetro
//const int pinoVolume = A0;

// Botões
const int botaoNota    = 2;
const int botaoCorreto = 3;
const int botaoErrado  = 4;

// LEDs
const int ledVerde     = 5;
const int ledVermelho  = 6;

bool estadoAnterior[3] = {true, true, true};
unsigned long ultimoAcionamento[3] = {0, 0, 0};
const unsigned long debounceDelay = 250;
bool audioTocando = false;

void setup() {
  pinMode(botaoNota, INPUT_PULLUP);
  pinMode(botaoCorreto, INPUT_PULLUP);
  pinMode(botaoErrado, INPUT_PULLUP);

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
  // Controle de volume via potenciômetro
  //int leituraVolume = analogRead(pinoVolume);
  //int volumeDF = map(leituraVolume, 0, 1023, 0, 30);
  //mp3.volume(volumeDF);

  verificarBotao(0, botaoNota);
  verificarBotao(1, botaoCorreto);
  verificarBotao(2, botaoErrado);
  delay(10);
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
        mp3.playMp3Folder(5); // Cinco reais
        delay(1000);
        break;
      case 1:
        digitalWrite(ledVermelho, HIGH);
        mp3.playMp3Folder(1); // Parabéns
        delay(1500);
        digitalWrite(ledVermelho, LOW);
        break;
      case 2:
        Serial.println("Botão de ERRO pressionado");
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}
