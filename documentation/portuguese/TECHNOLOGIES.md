# Metodologias e Tecnologias

## Stack Principal

### Jogo Desktop

| Tecnologia | Versão | Função |
| ---------- | ------ | ------ |
| **C** | C11 no CMake | Linguagem principal do jogo. |
| **raylib** | Instalada no sistema | Janela, entrada de mouse, renderização 2D, texturas e áudio. |
| **CMake** | `>= 3.10` | Geração do build e link com a raylib. |
| **GCC/Clang** | Compilador C | Compilação do executável `game`. |
| **PNG** | Assets raster | Sprites da máquina, símbolos e animação dos reels. |
| **MP3** | Assets de áudio | Sons de roleta e game over. |

### Ferramentas de Desenvolvimento

| Ferramenta | Função |
| ---------- | ------ |
| **Git** | Controle de versão do projeto. |
| **VS Code** | Editor configurado em `.vscode/` para C/C++ e task GCC. |
| **CMake CLI** | Comandos `cmake -S . -B build` e `cmake --build build`. |
| **GCC task** | Alternativa local para compilar o arquivo ativo via `.vscode/tasks.json`. |

---

## Metodologia de Desenvolvimento

### Arquitetura Procedural Modular

O projeto separa responsabilidades por arquivos C e headers:

- **Entrada**: `src/main.c` inicializa raylib, áudio e loop principal.
- **Configuração**: `src/config/config.h` centraliza constantes.
- **Core**: `src/core/game.c` concentra estado, regras, animação e desenho.
- **Interface do Core**: `src/core/game.h` declara estados, funções e variáveis externas.

### Máquina de Estados

O fluxo principal usa dois enums:

| Enum | Estados |
| ---- | ------- |
| `SlotState` | `SLOT_STATIC`, `SLOT_SPINNING`, `SLOT_RESULT` |
| `GameState` | `GAMEPLAY`, `GAME_OVER` |

Essa divisão permite separar o estado da rodada da condição geral do jogo.

### Conventional Commits

O histórico usa mensagens próximas a Conventional Commits, como `feat:`, `fix:` e `refactor:`. Para manter consistência, novos commits devem usar mensagens curtas em português ou inglês técnico, descrevendo a mudança real.

---

## Gerenciamento de Estado e Dados

### Estado em Memória

| Aspecto | Implementação |
| ------- | ------------- |
| **Dinheiro** | Variável global `money`, iniciada com `INITIAL_MONEY`. |
| **Reels** | Array global `reels[3]`, sorteado com `rand() % FRUITS`. |
| **Rodada** | `slot_state` controla parado, girando e resultado. |
| **Jogo** | `game_state` controla gameplay e game over. |
| **Timers** | `spin_timer`, `lose_message_timer` e `shake_timer`, atualizados com `GetFrameTime()`. |
| **Texturas** | `Texture2D` globais para máquina, símbolos e quadros de animação. |
| **Sons** | `Sound` globais para roleta e game over. |

### Persistência

O projeto não usa banco de dados, arquivos de save ou configuração externa. Toda a sessão vive em memória e é reiniciada ao fechar o jogo ou clicar em `TRY AGAIN` na tela de game over.

### Comunicação com Sistema Operacional

| Aspecto | Implementação |
| ------- | ------------- |
| **Janela** | `InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)`. |
| **Áudio** | `InitAudioDevice()` e `LoadSound()`. |
| **Entrada** | `IsMouseButtonPressed(MOUSE_BUTTON_LEFT)` e `GetMousePosition()`. |
| **Renderização** | `BeginDrawing()`, `ClearBackground()`, `DrawTexture()`, `DrawTextureEx()` e `DrawText()`. |
| **Tempo** | `SetTargetFPS(DEFAULT_FPS)` e `GetFrameTime()`. |
