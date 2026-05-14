# Padrões de Organização e Nomeação

## Naming Conventions

### Código C

| Elemento | Convenção | Exemplo |
| -------- | --------- | ------- |
| **Funções públicas do jogo** | `PascalCase` | `InitGame()`, `UpdateGame()`, `DrawGame()` |
| **Funções de ação** | `PascalCase` com verbo | `StartSpin()`, `WinGame()`, `LoseGame()` |
| **Variáveis globais** | `snake_case` | `slot_state`, `spin_timer`, `lose_message_timer` |
| **Arrays globais** | `snake_case` plural | `reels[3]`, `animation[3]` |
| **Constantes/Macros** | `SCREAMING_SNAKE_CASE` | `WINDOW_WIDTH`, `INITIAL_MONEY`, `DEFAULT_FPS` |
| **Enums** | `PascalCase` | `SlotState`, `GameState` |
| **Valores de enum** | `SCREAMING_SNAKE_CASE` | `SLOT_STATIC`, `SLOT_SPINNING`, `GAME_OVER` |
| **Structs** | `PascalCase` | `Animation` |
| **Arquivos fonte** | `snake_case` ou nome simples | `main.c`, `game.c` |
| **Headers** | Mesmo nome do módulo | `game.h`, `config.h` |

### Assets

| Elemento | Convenção | Exemplo |
| -------- | --------- | ------- |
| **Sprites principais** | Nome descritivo em camelCase/Pascal misto existente | `slotMachine.png`, `crucifix.png` |
| **Quadros de animação** | Prefixo comum + número sequencial | `mistery1.png`, `mistery10.png` |
| **Áudio** | Nome curto descritivo | `roleta.mp3`, `gameover.mp3` |

---

## Padrão de Sufixos por Tipo de Arquivo

| Sufixo | Tipo | Responsabilidade |
| ------ | ---- | ---------------- |
| `.c` | Fonte C | Implementação compilável ou incluída no build. |
| `.h` | Header C | Declarações, constantes, enums e contratos de módulo. |
| `.png` | Sprite | Texturas carregadas via `LoadTexture()`. |
| `.mp3` | Áudio | Sons carregados via `LoadSound()`. |
| `.json` | Configuração de editor | Configurações e tasks do VS Code. |
| `.md` | Documentação | README, documentação técnica e notas. |
| `.txt` | Anotações livres | Registro de aprendizado em `notes.txt`. |

---

## Design Patterns Utilizados

### Game Loop Pattern

O jogo usa o padrão clássico de loop:

```c
while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
}
```

`UpdateGame()` altera estado e timers. `DrawGame()` renderiza o frame atual.

### State Machine Pattern

`SlotState` e `GameState` evitam que todas as ações sejam tratadas por condicionais soltas. Cada estado habilita comportamentos específicos:

```text
SLOT_STATIC   → espera clique para iniciar spin
SLOT_SPINNING → sorteia reels e anima
SLOT_RESULT   → calcula vitória/perda e aguarda próximo clique
GAME_OVER     → desenha tela final e botão de reinício
```

### Resource Ownership

As texturas e sons principais são carregados em `InitGame()` e liberados no final de `main()`. Esse padrão mantém o ciclo de vida dos recursos alinhado ao ciclo de vida da aplicação.

### Compile-Time Configuration

Valores fixos de janela e economia ficam em `config.h`, permitindo alterar comportamento sem procurar números mágicos no core:

```c
#define INITIAL_MONEY 5000
#define WITHDRAW_MONEY 500
#define GAIN_MONEY 4000
```

### Runtime Asset Loading

O jogo carrega assets com caminhos relativos:

```c
LoadTexture("../assets/sprites/slotMachine.png");
LoadSound("../assets/audio/roleta.mp3");
```

Por isso, a execução esperada é a partir do diretório `build/`, onde `../assets/` aponta para a pasta versionada de assets.

---

## Organização de Diretórios por Responsabilidade

O projeto segue agrupamento por responsabilidade técnica:

```text
src/main.c           → entrada e loop raylib
src/config/config.h  → constantes globais do jogo
src/core/game.h      → interface pública do core
src/core/game.c      → implementação da slot machine
assets/sprites/      → imagens usadas na renderização
assets/audio/        → sons usados em runtime
documentation/       → documentação operacional e arquitetural
```

Essa organização é simples e adequada para um jogo pequeno. Se o projeto crescer, o próximo passo natural seria separar animação, áudio, assets e regras da slot machine em módulos próprios.
