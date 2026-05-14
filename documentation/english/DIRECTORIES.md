# Directory Mapping

## Full Structure

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

Local directories ignored by `.gitignore`, such as `build/`, `raylib/`, `.agent/`, `.agents/`, and `.codex/`, are not part of the versioned application source.

---

## Source Code — Directory Details

### `src/`

Main C source directory. It keeps the entry point, configuration, and slot machine logic.

| File/Directory | Responsibility |
| -------------- | -------------- |
| `main.c` | Entry point. Initializes raylib, audio, FPS, calls `InitGame()`, and runs `UpdateGame()` and `DrawGame()` until the window closes. |
| `config/` | Groups compile-time constants used by the game. |
| `core/` | Groups the main game logic and its public interface. |

### `src/config/`

| File | Responsibility |
| ---- | -------------- |
| `config.h` | Defines `WINDOW_TITLE`, `WINDOW_WIDTH`, `WINDOW_HEIGHT`, `INITIAL_MONEY`, `WITHDRAW_MONEY`, `GAIN_MONEY`, `DEFAULT_VOLUME`, and `DEFAULT_FPS`. |

### `src/core/`

| File | Responsibility |
| ---- | -------------- |
| `game.h` | Declares `SlotState`, `GameState`, game lifecycle functions, and external game variables. |
| `game.c` | Implements initialization, animation, reel randomization, symbol drawing, win, loss, game over, and mouse interaction. |

---

## Assets — Directory Details

### `assets/sprites/`

Sprites loaded by `LoadTexture()` in `InitGame()`.

| File | Dimensions | Usage |
| ---- | ---------- | ----- |
| `slotMachine.png` | `400 x 400` | Base slot machine image. |
| `crucifix.png` | `31 x 36` | Final symbol for fruit/reel `0`. |
| `seven.png` | `31 x 36` | Final symbol for fruit/reel `1`. |
| `skull.png` | `31 x 36` | Final symbol for fruit/reel `2`. |

### `assets/sprites/animation/`

Sequence of 10 PNG sprites (`mistery1.png` through `mistery10.png`) used during `SLOT_SPINNING`. All frames are `31 x 36`.

### `assets/audio/`

| File | Usage in current code |
| ---- | --------------------- |
| `roleta.mp3` | Loaded into `roulette_sound` and played when a spin starts. |
| `gameover.mp3` | Loaded into `game_over_sound` and played when entering game over. |
| `grito.mp3` | Versioned, but not loaded by the current implementation. |

---

## Editor Configuration

### `.vscode/`

| File | Responsibility |
| ---- | -------------- |
| `c_cpp_properties.json` | Configures Linux IntelliSense with `/usr/bin/gcc`, C17 for the editor, and workspace include path. |
| `settings.json` | Associates `config.h` and `math.h` with the C language. |
| `tasks.json` | Defines a GCC task for the active file with `-lraylib`, `-lm`, `-lpthread`, `-ldl`, `-lrt`, and `-lX11`. |

---

## Root Files

| File | Responsibility |
| ---- | -------------- |
| `CMakeLists.txt` | Official project build configuration. Uses minimum CMake `3.10`, C11, executable `game`, and `find_package(raylib REQUIRED)`. |
| `README.md` | Bilingual overview, technical documentation links, and project structure. |
| `notes.txt` | Study notes about raylib functions used in the project. |
| `.gitignore` | Ignores local artifacts: `build`, `raylib`, `.agent`, `.agents`, and `.codex`. |
