# 🎮 c-game-raylib

Um pequeno jogo 2D escrito em C usando a biblioteca raylib. Este repositório contém o código-fonte, os assets e os arquivos de build para que você possa compilar e executar o projeto em plataformas desktop.

## 🚀 O Jogo

- Um jogo/demo 2D minimalista que demonstra tratamento de entrada, renderização, loop de jogo simples e gerenciamento de assets usando raylib.
- Lida com entrada do teclado (e opcionalmente do mouse) para controlar o jogador, renderiza sprites da pasta `assets/sprites/` e reproduz áudio de `assets/audio/`.
- Projetado como um projeto de aprendizado para a matéria de Programação de Computadores I do curso de Engenharia de Software da UEPG.

## 🧩 Recursos

- Loop de jogo básico (update -> draw)
- Renderização de sprites e suporte simples a animação
- Reprodução de áudio (música de fundo / efeitos sonoros)
- Configurável via `src/config/config.h`

## ⚙️ Dependências

Você precisa dos seguintes itens para compilar e executar o jogo:

- Compilador C (GCC ou Clang) com suporte a C11
- CMake (recomendado) ou um ambiente Make funcional
- Biblioteca raylib (https://www.raylib.com/) — biblioteca auxiliar para gráficos/áudio/entrada
- Bibliotecas do sistema típicas: math, pthread, dl, rt, X11 (no Linux)

Dica: em muitas distribuições Linux você pode instalar o raylib pelo gerenciador de pacotes ou compilá-lo a partir do código-fonte. No Windows e macOS, siga as instruções oficiais de instalação do raylib.

## Métodos de Instalação

#### (Ubuntu / Debian) — comandos de instalação

```bash
# instalar ferramentas de build e dependência
sudo apt update
sudo apt install build-essential git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev gcc

# instalação da raylib e cmake (instalar em uma pasta universal ou onde mantém os programas)
sudo apt install cmake
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
sudo ldconfig
```

Para instalar a biblioteca `raylib` siga os passos de instalação (especificamente os passos para desenvolvimento com CMake) disponíveis em: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux e instale-a universalmente na pasta /opt ou /usr/local ou qualquer pasta que esteja acima de onde você salvar o jogo.

## 🖥️ Sistemas Operacionais Suportados

- Linux (testado)
- macOS (provavelmente — raylib tem suporte para macOS)
- Windows (MSYS2 / MinGW ou Visual Studio com raylib)

Observação: dependências específicas por plataforma (X11, backends de áudio) variam conforme o sistema. O build usa CMake, portanto deve se adaptar às plataformas suportadas pelo raylib.

## 📁 Arquitetura

Estrutura:

- `CMakeLists.txt` — configuração de build principal com CMake
- `src/` — arquivos fonte em C
  - `main.c` — ponto de entrada; inicializa o motor e inicia o loop do jogo
  - `core/game.c`, `core/game.h` — lógica principal do jogo, loop de update/draw e gerenciamento de estado
  - `utils/` — utilitários e pequenos subsistemas
  - `config/config.h` — constantes e configuração em tempo de compilação
- `assets/` — assets do jogo
  - `assets/sprites/` — sprites de imagens
  - `assets/audio/` — músicas e efeitos sonoros
- `build/` — artefatos locais do CMake e o binário compilado (`build/game`)

Resumo:

- Loop principal single-thread: `main` inicializa o raylib, carrega assets e entra no loop update->draw.
- Módulos por responsabilidade: tratamento de entrada, estado do jogo, renderização e gerenciamento de recursos estão separados em pequenos módulos C sob `src/` e `src/core`.
- Propriedade simples de recursos: o jogo carrega texturas e sons na inicialização e libera na saída (veja `core/game.c`).
- Build com CMake: mantém o sistema de build simples e multiplataforma.

Contrato de design (resumido):

- Entrada: eventos do teclado/mouse => atualizações do estado do jogo
- Atualização: a lógica do jogo modifica o estado na memória a cada frame
- Render: desenha o estado atual na tela usando raylib

Casos de borda considerados:

- Assets ausentes: o jogo imprime erros em stderr quando não consegue carregar recursos — verifique se a pasta `assets/` está presente.
- Plataforma não suportada: certifique-se de que o raylib esteja instalado para o seu sistema operacional.
- Tamanhos de janela grandes ou proporções inesperadas: a renderização atualmente segue as suposições do código (ajuste `config` se necessário).

## 🛠️ Compilar e executar

Usando CMake (recomendado):

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
# executar o binário do jogo (a partir da raiz do projeto)
./build/game
```

Se um `Makefile` estiver disponível ou se preferir executar pelo editor, também é possível usar a task de build fornecida (veja as tasks do seu editor).

## ✅ Checklist rápido antes de executar

- Instalar o raylib e dependências do sistema
- Garantir que a pasta `assets/` exista e contenha os arquivos esperados
- Compilar o projeto (CMake ou Make)

---
