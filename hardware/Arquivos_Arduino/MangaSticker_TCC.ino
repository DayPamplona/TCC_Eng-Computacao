
// =========================================
//             ATIVIDADE NÍVEL FÁCIL
// =========================================

// ----- Conteúdo de facil_1_de_3.ino -----

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


// ----- Conteúdo de facil_2_de_3.ino -----

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


// ----- Conteúdo de facil_3_de_3.ino -----

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



// =========================================
//             ATIVIDADE NÍVEL INTERMEDIÁRIO
// =========================================

// ----- Conteúdo de intermediario_1_de_3.ino -----

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


// ----- Conteúdo de intermediario_2_de_3.ino -----

// Projeto TCC sem multiplexador
// Atividade Intermediária - Página 2 com 6 botões e 3 LEDs (5+5+10)

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões
const int botaoNota5mais1 = 2;
const int botaoNota5mais2 = 3;
const int botaoNota10igual = 4;
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
  pinMode(botaoNota5mais1, INPUT_PULLUP);
  pinMode(botaoNota5mais2, INPUT_PULLUP);
  pinMode(botaoNota10igual, INPUT_PULLUP);
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

  verificarBotao(0, botaoNota5mais1);
  verificarBotao(1, botaoNota5mais2);
  verificarBotao(2, botaoNota10igual);
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
        mp3.playMp3Folder(8); // Cinco reais... mais
        delay(1500);
        break;
      case 1:
        mp3.playMp3Folder(8); // Cinco reais... mais (mesmo áudio)
        delay(1500);
        break;
      case 2:
        mp3.playMp3Folder(10); // Dez reais... igual
        delay(1500);
        break;
      case 3:
        digitalWrite(ledVermelho1, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho1, LOW);
        break;
      case 4:
        digitalWrite(ledVermelho2, HIGH);
        mp3.playMp3Folder(2); // Tente novamente
        delay(1500);
        digitalWrite(ledVermelho2, LOW);
        break;
      case 5:
        digitalWrite(ledVerde, HIGH);
        mp3.playMp3Folder(1); // Parabéns
        delay(1500);
        digitalWrite(ledVerde, LOW);
        break;
    }

    audioTocando = false;
  }

  estadoAnterior[indice] = estadoAtual;
}


// ----- Conteúdo de intermediario_3_de_3.ino -----

// Projeto TCC sem multiplexador
// Atividade Intermediária - Página 3 com 6 botões e 3 LEDs

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// DFPlayer
SoftwareSerial mySerial(11, 10); // RX, TX
DFRobotDFPlayerMini mp3;

// Botões
const int botaoInstrucao = 2;
const int botaoNota10menos = 3;
const int botaoNota5igual = 4;
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
  pinMode(botaoNota10menos, INPUT_PULLUP);
  pinMode(botaoNota5igual, INPUT_PULLUP);
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
  verificarBotao(1, botaoNota10menos);
  verificarBotao(2, botaoNota5igual);
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
        mp3.playMp3Folder(11); // Instrução do menino
        delay(2000);
        break;
      case 1:
        mp3.playMp3Folder(12); // Dez reais... menos
        delay(1500);
        break;
      case 2:
        mp3.playMp3Folder(13); // Cinco reais... igual
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



// =========================================
//             ATIVIDADE NÍVEL DIFÍCIL
// =========================================

// ----- Conteúdo de dificil_1_de_3.ino -----

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


// ----- Conteúdo de dificil_2_de_3.ino -----

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


// ----- Conteúdo de dificil_3_de_3.ino -----

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


