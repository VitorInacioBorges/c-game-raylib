# Methodologies and Technologies

## Main Stack

### Desktop Game

| Technology | Version | Function |
| ---------- | ------- | -------- |
| **C** | C11 in CMake | Main game language. |
| **raylib** | Installed on the system | Windowing, mouse input, 2D rendering, textures, and audio. |
| **CMake** | `>= 3.10` | Build generation and raylib linking. |
| **GCC/Clang** | C compiler | Compilation of the `game` executable. |
| **PNG** | Raster assets | Machine sprite, symbols, and reel animation. |
| **MP3** | Audio assets | Roulette and game-over sounds. |

### Development Tools

| Tool | Function |
| ---- | -------- |
| **Git** | Project version control. |
| **VS Code** | Editor configured in `.vscode/` for C/C++ and a GCC task. |
| **CMake CLI** | `cmake -S . -B build` and `cmake --build build` commands. |
| **GCC task** | Local alternative for compiling the active file through `.vscode/tasks.json`. |

---

## Development Methodology

### Modular Procedural Architecture

The project separates responsibilities by C files and headers:

- **Entry**: `src/main.c` initializes raylib, audio, and the main loop.
- **Configuration**: `src/config/config.h` centralizes constants.
- **Core**: `src/core/game.c` contains state, rules, animation, and drawing.
- **Core Interface**: `src/core/game.h` declares states, functions, and external variables.

### State Machine

The main flow uses two enums:

| Enum | States |
| ---- | ------ |
| `SlotState` | `SLOT_STATIC`, `SLOT_SPINNING`, `SLOT_RESULT` |
| `GameState` | `GAMEPLAY`, `GAME_OVER` |

This split separates the round state from the overall game condition.

### Conventional Commits

The history uses messages close to Conventional Commits, such as `feat:`, `fix:`, and `refactor:`. To stay consistent, new commits should use short Portuguese or technical English messages describing the actual change.

---

## State and Data Management

### In-Memory State

| Aspect | Implementation |
| ------ | -------------- |
| **Money** | Global variable `money`, initialized with `INITIAL_MONEY`. |
| **Reels** | Global array `reels[3]`, randomized with `rand() % FRUITS`. |
| **Round** | `slot_state` controls static, spinning, and result states. |
| **Game** | `game_state` controls gameplay and game over. |
| **Timers** | `spin_timer`, `lose_message_timer`, and `shake_timer`, updated with `GetFrameTime()`. |
| **Textures** | Global `Texture2D` values for machine, symbols, and animation frames. |
| **Sounds** | Global `Sound` values for roulette and game over. |

### Persistence

The project does not use a database, save files, or external configuration. The full session lives in memory and is reset when the game closes or when the player clicks `TRY AGAIN` on the game-over screen.

### Operating System Communication

| Aspect | Implementation |
| ------ | -------------- |
| **Window** | `InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)`. |
| **Audio** | `InitAudioDevice()` and `LoadSound()`. |
| **Input** | `IsMouseButtonPressed(MOUSE_BUTTON_LEFT)` and `GetMousePosition()`. |
| **Rendering** | `BeginDrawing()`, `ClearBackground()`, `DrawTexture()`, `DrawTextureEx()`, and `DrawText()`. |
| **Time** | `SetTargetFPS(DEFAULT_FPS)` and `GetFrameTime()`. |
