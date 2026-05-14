# Project Architecture

## Architecture Rationale

The project adopts a **modular procedural architecture in C**, centered on a raylib game loop and a small state machine that controls the slot machine. This choice addresses three core problems in this project:

1. **Low complexity for learning**: The main flow stays visible in a few files, making initialization, update, drawing, and shutdown easier to study.
2. **Direct raylib integration**: The logic uses raylib functions without an intermediate layer, reducing boilerplate in a small academic project.
3. **Explicit game state**: Money, reels, timers, textures, sounds, and states are stored in global variables controlled by lifecycle functions.

The architecture does not try to apply Clean Architecture or object orientation. For the current size, the separation by responsibility between `main.c`, `config.h`, `game.h`, and `game.c` is enough and keeps the focus on game behavior.

---

## Architecture Diagram

```text
┌─────────────────────────────────────────────────────────────┐
│                         src/main.c                          │
│  InitWindow → InitAudioDevice → InitGame → main loop        │
│  UpdateGame → DrawGame → unload resources → CloseWindow     │
└──────────────────────────────┬──────────────────────────────┘
                               │
┌──────────────────────────────▼──────────────────────────────┐
│                       src/core/game.c                       │
│  States, reel randomization, timers, animation, win, loss,  │
│  game-over screen, sprite drawing, and sounds.              │
└───────────────┬───────────────────────────────┬─────────────┘
                │                               │
┌───────────────▼──────────────┐  ┌─────────────▼──────────────┐
│      src/config/config.h     │  │           assets/          │
│  Window, FPS, money, spin    │  │  PNG sprites, animation    │
│  cost, and reward constants. │  │  frames, and MP3 sounds.   │
└──────────────────────────────┘  └────────────────────────────┘
```

---

## Data Flow — Slot Machine Round

### Player Spin

```text
1. The player clicks the left mouse button.
2. UpdateGame() detects the click while in SLOT_STATIC.
3. StartSpin() subtracts WITHDRAW_MONEY from the balance.
4. StartSpin() changes slot_state to SLOT_SPINNING and plays roleta.mp3.
5. For 11 seconds, UpdateGame() randomizes reels[0..2] every frame.
6. DrawGame() displays the mistery1.png to mistery10.png animation on the three reels.
7. When spin_timer reaches zero, the state changes to SLOT_RESULT.
8. If all three reels match, WinGame() adds GAIN_MONEY.
9. If they do not match, LoseGame() enables the loss message and visual shake.
10. On the next click, the game returns to SLOT_STATIC or enters GAME_OVER.
```

### Game Over

```text
1. In SLOT_RESULT, if money <= 0 and the player clicks, game_state changes to GAME_OVER.
2. gameover.mp3 is played.
3. DrawGame() delegates to DrawGameOver().
4. DrawGameOver() draws the black screen, message, and TRY AGAIN button.
5. Clicking the button resets money, slot_state, and game_state.
```

---

## Dependency Direction

The entry point depends directly on configuration and the game core:

```c
#include "./config/config.h"
#include "./core/game.c"
```

`src/core/game.c` includes `game.h`, `config.h`, raylib, and standard libraries (`stdlib.h`, `stdio.h`, `time.h`). `game.h` exposes lifecycle functions and external variables used by the entry point.

> Technical note: `main.c` includes `game.c` directly. This works because `CMakeLists.txt` compiles only `src/*.c`; in this organization, the core implementation becomes part of the same compilation unit as `main.c`. In a larger project, the more common path would be to compile `src/core/game.c` separately and include only `game.h`.

---

## System Modules

| Module                | Responsibility                                                                           |
| --------------------- | ---------------------------------------------------------------------------------------- |
| `src/main.c`          | Initializes window and audio, sets FPS, runs the main loop, and releases main resources. |
| `src/config/config.h` | Defines window, title, initial money, spin cost, reward, and FPS constants.              |
| `src/core/game.h`     | Declares enums, public core functions, and shared external variables.                    |
| `src/core/game.c`     | Implements states, randomization, animations, drawing, win/loss rules, and game over.    |
| `assets/sprites/`     | Contains the machine, final symbols, and reel animation frames.                          |
| `assets/audio/`       | Contains sound effects used by spin and game over.                                       |
| `CMakeLists.txt`      | Defines the CMake build, C11 standard, `build/` output, and raylib linking.              |
