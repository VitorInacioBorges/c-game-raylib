# 🇧🇷 c-game-raylib (PORTUGUESE)

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

## 🗂️ Esquema de pastas (visão rápida)

Uma representação simples da estrutura atual do projeto:

```
c-game-raylib/
├── CMakeLists.txt
├── README.md
├── assets/
│   ├── audio/
│   └── sprites/
├── build/
│   └── (artefatos do CMake e binário)
└── src/
    ├── main.c
    ├── config/
    │   └── config.h
    ├── core/
    │   ├── game.c
    │   └── game.h
    └── utils/
```

Este diagrama mostra a organização principal: `src` com lógica do jogo, `assets` com mídias e `build` com artefatos gerados.

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

<br>

# 🇺🇸 c-game-raylib (ENGLISH)

A small 2D game written in C using the raylib library. This repository contains the source code, assets and build files so you can compile and run the project on desktop platforms.

## 🚀 The Game

- A minimal 2D game/demo that demonstrates input handling, rendering, a simple game loop and asset management using raylib.
- Handles keyboard (and optionally mouse) input to control the player, renders sprites from `assets/sprites/` and plays audio from `assets/audio/`.
- Designed as a learning project for the Computer Programming subject of Ponta Grossa's State University.

## 🧩 Features

- Basic game loop (update -> draw)
- Sprite rendering and simple animation support
- Audio playback (background music / SFX)
- Configurable via `src/config/config.h`

## ⚙️ Dependencies

You need the following to build and run the game:

- C compiler (GCC or Clang) supporting C11
- CMake (recommended) or a working Make environment
- raylib library (https://www.raylib.com/) — helper library for graphics/audio/input
- Typical system libraries: math, pthread, dl, rt, X11 (on Linux)

Tip: On many Linux distributions you can install raylib from the package manager or build it from source. On Windows and macOS follow raylib's official installation instructions.

## ⚙️ Installation Methods

#### Example (Ubuntu / Debian) — install commands

```bash
# install build tools and dependencies (example)
sudo apt update
sudo apt install build-essential git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev gcc

# installation of raylib and cmake (install in a universal folder or where you keep programs)
sudo apt install cmake
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
sudo ldconfig
```

If `libraylib-dev` is not available, follow raylib's build instructions to compile and install it.

## 🖥️ Supported Operating Systems

- Linux (tested)
- macOS (likely — raylib supports macOS)
- Windows (MSYS2 / MinGW or Visual Studio with raylib)

Note: Platform-specific dependencies (X11, audio backends) differ by OS. The build uses CMake so it should adapt across platforms supported by raylib.

## 📁 Project Layout / Software Architecture

High-level layout:

- `CMakeLists.txt` — top-level CMake build
- `src/` — C source files
  - `main.c` — entry point; initializes engine and starts game loop
  - `core/game.c`, `core/game.h` — core game logic, update/draw loop and state management
  - `utils/` — helper utilities and small subsystems
  - `config/config.h` — compile-time configuration and constants
- `assets/` — game assets
  - `assets/sprites/` — image sprites
  - `assets/audio/` — music and sound effects
- `build/` — local CMake artifacts and the compiled binary (`build/game`)

Architecture summary:

- Single-threaded main loop: `main` initializes raylib, loads assets, and enters an update->draw loop.
- Modules by responsibility: input handling, game state, rendering, and resource management are separated into small C modules under `src/` and `src/core`.
- Simple resource ownership: the game loads textures and sounds at startup and frees them on exit (see `core/game.c`).
- Build with CMake: keeps the build system simple and cross-platform.

## 🗂️ Folder Scheme (quick view)

```
c-game-raylib/
├── CMakeLists.txt
├── README.md
├── assets/
│   ├── audio/
│   └── sprites/
├── build/
│   └── (cmake artifacts and binary)
└── src/
    ├── main.c
    ├── config/
    │   └── config.h
    ├── core/
    │   ├── game.c
    │   └── game.h
    └── utils/
```

## 🛠️ Build & Run

Using CMake (recommended):

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
# run the game binary (from project root)
./build/game
```

## ✅ Quick checklist before running

- Install raylib and system dependencies
- Ensure `assets/` folder exists and contains expected files
- Build the project (CMake or Make)

---
