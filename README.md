# MangaSticker para Ensino de Matemática em Pessoas com Síndrome de Down

**Projeto Desenvolvido**

Este repositório contém os **códigos**, **arquivos de hardware**, **documentação** e **materiais relacionados ao Trabalho de Conclusão de Curso (TCC)** da estudante **Dayana Stefany Costa Pamplona**, da **Escola Politécnica e de Artes da PUC Goiás**.

O projeto tem como foco a criação de **atividades interativas** utilizando o **MangaSticker**, uma ferramenta que combina histórias ilustradas (**mangás**) com circuitos adesivos (**circuit stickers**).  

O objetivo é apoiar o ensino de **conceitos básicos de matemática e educação financeira para pessoas com Síndrome de Down**, promovendo **atenção, engajamento e aprendizagem de forma lúdica e acessível.**

https://repositorio.pucgoias.edu.br/jspui/handle/123456789/9367

---

## Objetivos

- Desenvolver **atividades interativas** utilizando estímulos visuais, sonoros e táteis.
- Facilitar o ensino de **conceitos matemáticos básicos**, como identificação de valores e operações simples.
- Avaliar se o uso de recursos interativos **contribui para melhorar a atenção e o engajamento** de pessoas com Síndrome de Down durante as atividades.

---

## Tecnologias e Ferramentas Utilizadas

- **Arduino UNO** — Controle dos circuitos.
- **MangaSticker (Python + Processing IDE)** — Desenvolvimento das histórias interativas.
- **DFPlayer Mini** — Reprodução de áudios nas atividades.
- **Circuitos Adesivos** — Montagem com fita de cobre, LEDs SMD 3528 e botões SMD 4x4mm.
- **Emolab** — Análise de dados de atenção e engajamento via reconhecimento facial.
- **Excel + Python** — Análise estatística dos dados.

---

## Estrutura do Repositório

/hardware/ → Esquemáticos, diagramas e mapeamento dos circuitos.
/docs/ → Documentação, monografia, slides e imagens do projeto.
/dados/ → Dados coletados dos testes, relatórios e scripts de análise.
/referencias/ → Artigos, manuais técnicos (datasheets) e bibliografia usada.
/codigo/ → Códigos Arduino, MangaSticker e scripts auxiliares.


---

## Como Executar o Projeto

### Arduino

1. Abra o arquivo **`MangaSticker_TCC.ino`** na **IDE do Arduino**.
2. Instale as bibliotecas necessárias listadas em **`/referencias/bibliotecas_arduino.txt`**.
3. Faça o **upload do código** para a placa **Arduino UNO**.
4. Monte os circuitos seguindo os esquemáticos disponíveis em **`/hardware/`**.

---

### 🖥️ MangaSticker (Software)

1. Clone este repositório:

```bash
git clone https://github.com/DayPamplona/TCC_MangaSticker_SD.git

Instale o software Processing IDE.

Abra o arquivo MangaSticker.pde localizado na pasta /codigo/MangaSticker/.

Execute o programa para visualizar e interagir com o mangá educativo.

👥 Público-Alvo
Pessoas com Síndrome de Down, especialmente jovens e adultos.

Educadores e profissionais de inclusão.

Pesquisadores interessados em tecnologias assistivas, acessibilidade e ensino de matemática.


---

### ✔️ **O que você faz agora:**  
1. Salva isso num arquivo chamado **`README.md`** na pasta principal do seu repositório (`TCC_MangaSticker_SD/`).  
2. Faz:

```bash
git add README.md
git commit -m "Adicionando README com descrição do projeto"
git push

