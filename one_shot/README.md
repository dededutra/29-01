# Projetos para Raspberry Pi Pico – Semáforo Periódico e Temporizador One-Shot com Botão

Este repositório contém dois programas desenvolvidos para o Raspberry Pi Pico (ou Pico W) utilizando o Pico SDK. Os projetos foram configurados para serem compilados e carregados utilizando o Visual Studio Code (VS Code) com a extensão oficial para Raspberry Pi Pico.

## Sumário

- [Projetos para Raspberry Pi Pico – Semáforo Periódico e Temporizador One-Shot com Botão](#projetos-para-raspberry-pi-pico--semáforo-periódico-e-temporizador-one-shot-com-botão)
  - [Sumário](#sumário)
  - [Programa 1: Semáforo Periódico](#programa-1-semáforo-periódico)
    - [Descrição](#descrição)
    - [Funcionamento](#funcionamento)
  - [Programa 2: Temporizador One-Shot com Botão](#programa-2-temporizador-one-shot-com-botão)
    - [Descrição](#descrição-1)
    - [Funcionamento](#funcionamento-1)
  - [Configuração do Ambiente com VS Code](#configuração-do-ambiente-com-vs-code)
  - [Compilação](#compilação)

## Programa 1: Semáforo Periódico

### Descrição

Este programa implementa um semáforo utilizando a função `add_repeating_timer_ms()` do Pico SDK. O semáforo alterna os estados dos LEDs (configurados, por exemplo, em um LED RGB com os pinos 11, 12 e 13) de forma periódica a cada 3 segundos:
- Estado inicial: LED vermelho aceso.
- Em seguida: combinação que gera o amarelo (ativando simultaneamente o vermelho e o verde).
- Por fim: LED verde aceso.

### Funcionamento

- O programa inicia com o LED vermelho aceso.
- Em cada transição (a cada 3000 ms), os LEDs são alterados conforme a sequência definida.
- Mensagens de debug são enviadas via serial para monitoramento.

## Programa 2: Temporizador One-Shot com Botão

### Descrição

Este programa utiliza a função `add_alarm_in_ms()` para criar um temporizador one-shot. A sequência é iniciada ao pressionar um botão (por exemplo, Botão A no GPIO 5) e segue os passos:
1. Imediatamente após o clique: os três LEDs (vermelho, azul e verde) são ligados.
2. Após 3 segundos: um LED é desligado (ficam ligados dois LEDs).
3. Após mais 3 segundos: um segundo LED é desligado (apenas um LED permanece aceso).
4. Após mais 3 segundos: o último LED é desligado (todos os LEDs apagados).

A nova sequência só pode ser iniciada após todos os LEDs estarem desligados.

### Funcionamento

- A sequência de transição é gerenciada via callbacks one-shot, reagendando um novo alarme a cada etapa.
- O programa implementa um debounce simples para evitar disparos indesejados devido ao bouncing do botão.
- As mensagens de debug acompanham as transições de estado via serial.

## Configuração do Ambiente com VS Code

Para configurar o ambiente de desenvolvimento para o Raspberry Pi Pico utilizando o VS Code e a extensão oficial, siga os passos abaixo:

1. **Instale o VS Code:**  
   Se ainda não o tiver, baixe e instale o [Visual Studio Code](https://code.visualstudio.com/).

2. **Instale a Extensão do Raspberry Pi Pico:**  
   - Abra o VS Code e acesse a aba de extensões (ícone de quadrado no lado esquerdo ou `Ctrl+Shift+X`).
   - Procure por “Raspberry Pi Pico” e instale a extensão oficial (geralmente, ela oferece integração com o Pico SDK, debug e upload via USB).

3. **Clone ou Abra o Repositório:**  
   Abra o repositório que contém os programas no VS Code. Certifique-se de que o arquivo `CMakeLists.txt` esteja configurado corretamente e referencie os arquivos fonte (por exemplo, `pico_traffic_light.c` e `matriz_rgb.c`).

4. **Configuração do Pico SDK:**  
   Verifique se o Pico SDK está instalado e configurado no seu sistema. Caso necessário, siga as instruções da [documentação oficial do Pico SDK](https://github.com/raspberrypi/pico-sdk).

5. **Configuração de CMake:**  
   O projeto deve conter um arquivo `CMakeLists.txt` com as configurações necessárias para compilar os projetos para o Pico. A extensão do VS Code pode invocar o CMake e o Ninja para a compilação.

## Compilação

Utilizando o VS Code com a extensão do Raspberry Pi Pico, o processo de compilação pode ser feito conforme os passos abaixo:

1. **Compilação:**
   - Abra o terminal integrado do VS Code (`Ctrl+``).
   - No terminal, navegue até a pasta do projeto e crie uma pasta de compilação, se necessário:
     ```bash
     mkdir build
     cd build
     cmake ..
     ninja
     ```
   - Alternativamente, a extensão pode oferecer comandos integrados para compilar o projeto.
   - **Simulação**
   - Utilizando o diagram.json dentro do ambiente VS Code pode se testar o funcionamento na simulação do wokwi.
   - 
