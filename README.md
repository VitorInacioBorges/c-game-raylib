<a id="portugues"></a>

# 🎰​ Jogo de Caça Níqueis

[Português](#portugues) 🇧🇷 / 🇵🇹 | [English](#english) 🇺🇸 / 🇬🇧 / 🇨🇦 / 🇦🇺

Jogo desktop 2D de slot machine criado em C com raylib por Vitor Inacio Borges.

## Propósito

Oferecer um projeto pequeno e executável para praticar programação em C, loop de jogo, controle de estado, renderização de sprites, áudio e uso da raylib em um jogo desktop. O projeto também funciona como material de aprendizado para Programação de Computadores I no curso de Engenharia de Software da UEPG.

## Objetivos

- **Slot Machine Jogável**: Simular três reels com símbolos sorteados, custo por rodada e recompensa por combinação.
- **Loop de Jogo com raylib**: Controlar inicialização, atualização, renderização, áudio e encerramento da janela.
- **Gerenciamento de Assets**: Carregar sprites, quadros de animação e sons a partir da pasta `assets/`.
- **Build Local Simples**: Compilar o jogo com CMake, GCC/Clang e raylib instalada no sistema.

## Serviços

| Serviço               | Descrição                                                                                        |
| --------------------- | ------------------------------------------------------------------------------------------------ |
| **Aplicação Desktop** | Binário `game` escrito em **C11**, usando **raylib** para janela, entrada, renderização e áudio. |
| **Build CMake**       | Configuração em `CMakeLists.txt` que gera o executável em `build/game` e linka com `raylib`.     |
| **Assets do Jogo**    | Sprites PNG e sons MP3 versionados em `assets/sprites/` e `assets/audio/`.                       |

## Documentação Técnica

| Documento                                                         | Descrição                                                |
| ----------------------------------------------------------------- | -------------------------------------------------------- |
| [ARCHITECTURE.md](./documentation/portuguese/ARCHITECTURE.md)     | Fundação arquitetural, estados do jogo e fluxo de dados  |
| [DIRECTORIES.md](./documentation/portuguese/DIRECTORIES.md)       | Mapeamento completo de diretórios e responsabilidades    |
| [TECHNOLOGIES.md](./documentation/portuguese/TECHNOLOGIES.md)     | Stack, metodologias e gerenciamento de estado            |
| [CONVENTIONS.md](./documentation/portuguese/CONVENTIONS.md)       | Padrões de nomeação, organização e patterns usados       |
| [BEST-PRACTICES.md](./documentation/portuguese/BEST-PRACTICES.md) | Práticas de C/raylib, testes manuais, riscos e segurança |
| [PREREQUISITES.md](./documentation/portuguese/PREREQUISITES.md)   | Dependências de sistema, ferramentas e hardware          |
| [EXECUTION.md](./documentation/portuguese/EXECUTION.md)           | Setup local, build, execução e verificação               |

## Estrutura Geral

```bash
c-game-raylib/
├── assets/
│   ├── audio/              # Efeitos sonoros e áudio de game over
│   └── sprites/            # Sprite da máquina, símbolos e animação dos reels
├── documentation/
│   ├── english/            # Documentação em Inglês
│   └── portuguese/         # Documentação em Português
├── src/
│   ├── config/             # Constantes de janela, FPS e economia do jogo
│   ├── core/               # Estado, loop, desenho, sorteio e regras da slot machine
│   └── main.c              # Ponto de entrada raylib
├── .vscode/                # Configuração local de editor e task GCC
├── CMakeLists.txt          # Build CMake
├── notes.txt               # Anotações de estudo sobre raylib
└── README.md               # Este arquivo
```

---

<a id="english"></a>

# 🎰​ Jackpot Game

[Português](#portugues) 🇧🇷 / 🇵🇹 | [English](#english) 🇺🇸 / 🇬🇧 / 🇨🇦 / 🇦🇺

A 2D desktop slot machine game written in C with raylib by Vitor Inacio Borges.

## Purpose

To provide a small executable project for practicing C programming, game loops, state control, sprite rendering, audio, and raylib usage in a desktop game. The project also serves as learning material for Computer Programming I in the Software Engineering course at UEPG.

## Objectives

- **Playable Slot Machine**: Simulate three reels with randomized symbols, spin cost, and reward on matching combinations.
- **raylib Game Loop**: Control initialization, update, rendering, audio, and window shutdown.
- **Asset Management**: Load sprites, animation frames, and sounds from the `assets/` folder.
- **Simple Local Build**: Compile the game with CMake, GCC/Clang, and raylib installed on the system.

## Services

| Service                 | Description                                                                                            |
| ----------------------- | ------------------------------------------------------------------------------------------------------ |
| **Desktop Application** | `game` binary written in **C11**, using **raylib** for windowing, input, rendering, and audio.         |
| **CMake Build**         | `CMakeLists.txt` configuration that outputs the executable to `build/game` and links against `raylib`. |
| **Game Assets**         | PNG sprites and MP3 sounds versioned in `assets/sprites/` and `assets/audio/`.                         |

## Technical Documentation

| Document                                                       | Description                                           |
| -------------------------------------------------------------- | ----------------------------------------------------- |
| [ARCHITECTURE.md](./documentation/english/ARCHITECTURE.md)     | Architectural foundation, game states, and data flow  |
| [DIRECTORIES.md](./documentation/english/DIRECTORIES.md)       | Complete mapping of directories and responsibilities  |
| [TECHNOLOGIES.md](./documentation/english/TECHNOLOGIES.md)     | Stack, methodologies, and state management            |
| [CONVENTIONS.md](./documentation/english/CONVENTIONS.md)       | Naming patterns, organization, and patterns used      |
| [BEST-PRACTICES.md](./documentation/english/BEST-PRACTICES.md) | C/raylib practices, manual tests, risks, and security |
| [PREREQUISITES.md](./documentation/english/PREREQUISITES.md)   | System dependencies, tools, and hardware              |
| [EXECUTION.md](./documentation/english/EXECUTION.md)           | Local setup, build, execution, and verification       |

## General Structure

```bash
c-game-raylib/
├── assets/
│   ├── audio/              # Sound effects and game-over audio
│   └── sprites/            # Machine sprite, symbols, and reel animation
├── documentation/
│   ├── english/            # English Documentation
│   └── portuguese/         # Portuguese Documentation
├── src/
│   ├── config/             # Window, FPS, and game economy constants
│   ├── core/               # State, loop, drawing, randomization, and slot rules
│   └── main.c              # raylib entry point
├── .vscode/                # Local editor configuration and GCC task
├── CMakeLists.txt          # CMake build
├── notes.txt               # Study notes about raylib
└── README.md               # This file
```
