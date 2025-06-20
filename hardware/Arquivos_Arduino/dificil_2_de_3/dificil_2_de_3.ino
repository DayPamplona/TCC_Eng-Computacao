// Projeto TCC sem multiplexador
// Atividade Difícil - Página 2 com 5 botões e 3 LEDs

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões
const int botaoSanduiche = 2;
const int botaoSuco = 3;
const int botaoRespostaErrada1 = 4;
const int botaoRespostaErrada2 = 5;
const int botaoRespostaCerta = 6;

// LEDs
const int ledVerde = 7;
const int ledVermelho1 = 8;
const int ledVermelho2 = 9;

bool estadoAnterior[5] = {true, true, true, true, true};
unsigned long ultimoAcionamento[5] = {0, 0, 0, 0, 0};
const unsigned long debounceDelay = 250;

void setup() {
  pinMode(botaoSanduiche, INPUT_PULLUP);
  pinMode(botaoSuco, INPUT_PULLUP);
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

  mp3.volume(15);
  Serial.println("DFPlayer iniciado com sucesso!");
}

void loop() {
  verificarBotao(0, botaoSanduiche);
  verificarBotao(1, botaoSuco);
  verificarBotao(2, botaoRespostaErrada1);
  verificarBotao(3, botaoRespostaErrada2);
  verificarBotao(4, botaoRespostaCerta);
  delay(10);
}

void verificarBotao(int indice, int pino) {
  bool estadoAtual = digitalRead(pino) == LOW;
  unsigned long agora = millis();

  if (estadoAtual && !estadoAnterior[indice] && (agora - ultimoAcionamento[indice] > debounceDelay)) {
    ultimoAcionamento[indice] = agora;
    Serial.print("Botão acionado no pino: ");
    Serial.println(pino);

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
        digitalWrite(ledVermelho1, HIGH);
        mp3.playMp3Folder(15); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho1, LOW);
        break;
      case 3:
        Serial.println("Acionando LED 9 - Resposta Errada 2");
        digitalWrite(ledVermelho2, HIGH);
        mp3.playMp3Folder(15); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho2, LOW);
        break;
      case 4:
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(14); // Parabéns (voz do menino)
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
    }
  }

  estadoAnterior[indice] = estadoAtual;
}
