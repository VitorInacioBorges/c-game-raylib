# Mapeamento de Diretórios

## Estrutura Completa

```bash
c-game-raylib/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── settings.json
│   └── tasks.json
├── assets/
│   ├── audio/
│   │   ├── gameover.mp3
│   │   ├── grito.mp3
│   │   └── roleta.mp3
│   └── sprites/
│       ├── animation/
│       │   ├── mistery1.png
│       │   ├── mistery2.png
│       │   ├── mistery3.png
│       │   ├── mistery4.png
│       │   ├── mistery5.png
│       │   ├── mistery6.png
│       │   ├── mistery7.png
│       │   ├── mistery8.png
│       │   ├── mistery9.png
│       │   └── mistery10.png
│       ├── crucifix.png
│       ├── seven.png
│       ├── skull.png
│       └── slotMachine.png
├── documentation/
│   ├── english/
│   │   ├── ARCHITECTURE.md
│   │   ├── BEST-PRACTICES.md
│   │   ├── CONVENTIONS.md
│   │   ├── DIRECTORIES.md
│   │   ├── EXECUTION.md
│   │   ├── PREREQUISITES.md
│   │   └── TECHNOLOGIES.md
│   └── portuguese/
│       ├── ARCHITECTURE.md
│       ├── BEST-PRACTICES.md
│       ├── CONVENTIONS.md
│       ├── DIRECTORIES.md
│       ├── EXECUTION.md
│       ├── PREREQUISITES.md
│       └── TECHNOLOGIES.md
├── src/
│   ├── config/
│   │   └── config.h
│   ├── core/
│   │   ├── game.c
│   │   └── game.h
│   └── main.c
├── .gitignore
├── CMakeLists.txt
├── notes.txt
└── README.md
```

Diretórios locais ignorados por `.gitignore`, como `build/`, `raylib/`, `.agent/`, `.agents/` e `.codex/`, não fazem parte do código versionado da aplicação.

---

## Código-Fonte — Detalhamento por Diretório

### `src/`

Diretório principal do código C. Mantém o ponto de entrada, a configuração e a lógica da slot machine.

| Arquivo/Diretório | Responsabilidade |
| ----------------- | ---------------- |
| `main.c` | Ponto de entrada. Inicializa raylib, áudio, FPS, chama `InitGame()`, executa `UpdateGame()` e `DrawGame()` até a janela fechar. |
| `config/` | Agrupa constantes de compilação usadas pelo jogo. |
| `core/` | Agrupa a lógica principal do jogo e sua interface pública. |

### `src/config/`

| Arquivo | Responsabilidade |
| ------- | ---------------- |
| `config.h` | Define `WINDOW_TITLE`, `WINDOW_WIDTH`, `WINDOW_HEIGHT`, `INITIAL_MONEY`, `WITHDRAW_MONEY`, `GAIN_MONEY`, `DEFAULT_VOLUME` e `DEFAULT_FPS`. |

### `src/core/`

| Arquivo | Responsabilidade |
| ------- | ---------------- |
| `game.h` | Declara `SlotState`, `GameState`, funções de ciclo de vida e variáveis externas do jogo. |
| `game.c` | Implementa inicialização, animação, sorteio dos reels, desenho dos símbolos, vitória, derrota, game over e interação por mouse. |

---

## Assets — Detalhamento por Diretório

### `assets/sprites/`

Sprites carregados por `LoadTexture()` em `InitGame()`.

| Arquivo | Dimensão | Uso |
| ------- | -------- | --- |
| `slotMachine.png` | `400 x 400` | Imagem base da máquina caça-níquel. |
| `crucifix.png` | `31 x 36` | Símbolo final do fruit/reel `0`. |
| `seven.png` | `31 x 36` | Símbolo final do fruit/reel `1`. |
| `skull.png` | `31 x 36` | Símbolo final do fruit/reel `2`. |

### `assets/sprites/animation/`

Sequência de 10 sprites PNG (`mistery1.png` até `mistery10.png`) usada durante o estado `SLOT_SPINNING`. Todos os quadros possuem `31 x 36`.

### `assets/audio/`

| Arquivo | Uso no código atual |
| ------- | ------------------- |
| `roleta.mp3` | Carregado em `roulette_sound` e tocado ao iniciar o spin. |
| `gameover.mp3` | Carregado em `game_over_sound` e tocado ao entrar em game over. |
| `grito.mp3` | Versionado, mas não carregado pela implementação atual. |

---

## Configuração de Editor

### `.vscode/`

| Arquivo | Responsabilidade |
| ------- | ---------------- |
| `c_cpp_properties.json` | Configura IntelliSense Linux com `/usr/bin/gcc`, padrão C17 para o editor e include path do workspace. |
| `settings.json` | Associa `config.h` e `math.h` à linguagem C. |
| `tasks.json` | Define uma task GCC para compilar o arquivo ativo com `-lraylib`, `-lm`, `-lpthread`, `-ldl`, `-lrt` e `-lX11`. |

---

## Arquivos de Raiz

| Arquivo | Responsabilidade |
| ------- | ---------------- |
| `CMakeLists.txt` | Configuração oficial de build do projeto. Usa CMake mínimo `3.10`, padrão C11, executável `game` e `find_package(raylib REQUIRED)`. |
| `README.md` | Visão geral bilíngue, links para documentação técnica e estrutura do projeto. |
| `notes.txt` | Anotações de estudo sobre funções da raylib usadas no projeto. |
| `.gitignore` | Ignora artefatos locais: `build`, `raylib`, `.agent`, `.agents` e `.codex`. |
