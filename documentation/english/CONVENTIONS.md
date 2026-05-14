# Organization and Naming Standards

## Naming Conventions

### C Code

| Element | Convention | Example |
| ------- | ---------- | ------- |
| **Public game functions** | `PascalCase` | `InitGame()`, `UpdateGame()`, `DrawGame()` |
| **Action functions** | Verb-based `PascalCase` | `StartSpin()`, `WinGame()`, `LoseGame()` |
| **Global variables** | `snake_case` | `slot_state`, `spin_timer`, `lose_message_timer` |
| **Global arrays** | Plural `snake_case` | `reels[3]`, `animation[3]` |
| **Constants/Macros** | `SCREAMING_SNAKE_CASE` | `WINDOW_WIDTH`, `INITIAL_MONEY`, `DEFAULT_FPS` |
| **Enums** | `PascalCase` | `SlotState`, `GameState` |
| **Enum values** | `SCREAMING_SNAKE_CASE` | `SLOT_STATIC`, `SLOT_SPINNING`, `GAME_OVER` |
| **Structs** | `PascalCase` | `Animation` |
| **Source files** | `snake_case` or simple name | `main.c`, `game.c` |
| **Headers** | Same name as the module | `game.h`, `config.h` |

### Assets

| Element | Convention | Example |
| ------- | ---------- | ------- |
| **Main sprites** | Existing descriptive mixed camel/Pascal name | `slotMachine.png`, `crucifix.png` |
| **Animation frames** | Common prefix + sequential number | `mistery1.png`, `mistery10.png` |
| **Audio** | Short descriptive name | `roleta.mp3`, `gameover.mp3` |

---

## File Type Suffix Standard

| Suffix | Type | Responsibility |
| ------ | ---- | -------------- |
| `.c` | C source | Buildable or included implementation. |
| `.h` | C header | Declarations, constants, enums, and module contracts. |
| `.png` | Sprite | Textures loaded through `LoadTexture()`. |
| `.mp3` | Audio | Sounds loaded through `LoadSound()`. |
| `.json` | Editor configuration | VS Code settings and tasks. |
| `.md` | Documentation | README, technical documentation, and notes. |
| `.txt` | Free notes | Learning notes in `notes.txt`. |

---

## Design Patterns Used

### Game Loop Pattern

The game uses the classic loop pattern:

```c
while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
}
```

`UpdateGame()` changes state and timers. `DrawGame()` renders the current frame.

### State Machine Pattern

`SlotState` and `GameState` prevent all actions from being handled by loose conditionals. Each state enables specific behavior:

```text
SLOT_STATIC   → waits for click to start spin
SLOT_SPINNING → randomizes reels and animates
SLOT_RESULT   → computes win/loss and waits for next click
GAME_OVER     → draws final screen and restart button
```

### Resource Ownership

Main textures and sounds are loaded in `InitGame()` and released at the end of `main()`. This keeps resource lifetime aligned with application lifetime.

### Compile-Time Configuration

Fixed window and economy values live in `config.h`, allowing behavior changes without hunting for magic numbers in the core:

```c
#define INITIAL_MONEY 5000
#define WITHDRAW_MONEY 500
#define GAIN_MONEY 4000
```

### Runtime Asset Loading

The game loads assets with relative paths:

```c
LoadTexture("../assets/sprites/slotMachine.png");
LoadSound("../assets/audio/roleta.mp3");
```

For that reason, the expected execution location is the `build/` directory, where `../assets/` points to the versioned assets folder.

---

## Directory Organization by Responsibility

The project follows grouping by technical responsibility:

```text
src/main.c           → entry point and raylib loop
src/config/config.h  → global game constants
src/core/game.h      → public core interface
src/core/game.c      → slot machine implementation
assets/sprites/      → images used during rendering
assets/audio/        → sounds used at runtime
documentation/       → operational and architectural documentation
```

This organization is simple and appropriate for a small game. If the project grows, the natural next step would be to split animation, audio, assets, and slot machine rules into their own modules.
