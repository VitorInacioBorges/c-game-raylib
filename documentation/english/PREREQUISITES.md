# Prerequisites and Performance

## System Dependencies

### Runtime and Build

| Dependency | Minimum Version | Verification |
| ---------- | --------------- | ------------ |
| **C compiler** | GCC or Clang with C11 support | `cc --version` |
| **CMake** | `>= 3.10` | `cmake --version` |
| **raylib** | Compatible with `find_package(raylib REQUIRED)` | `pkg-config --libs raylib` or CMake test |
| **Git** | Any modern version | `git --version` |

### Common Linux Libraries for raylib

| Dependency | Function |
| ---------- | -------- |
| `libasound2-dev` | ALSA audio backend. |
| `libx11-dev` | Windowing and input through X11. |
| `libxrandr-dev` | Resolution and monitor support. |
| `libxi-dev` | Input devices. |
| `libgl1-mesa-dev` / `libglu1-mesa-dev` | OpenGL/Mesa. |
| `libxcursor-dev` | X11 cursor support. |
| `libxinerama-dev` | Multi-monitor support. |
| `libwayland-dev` / `libxkbcommon-dev` | Wayland support when applicable. |

### Optional Tools

| Tool | Function |
| ---- | -------- |
| **VS Code** | Use the versioned settings in `.vscode/`. |
| **C/C++ extension** | IntelliSense, header associations, and GCC task execution. |
| **Ninja** | Alternative CMake generator, if preferred. |

---

## Project Dependencies

### Code

| Item | Category | Note |
| ---- | -------- | ---- |
| `src/main.c` | Entry point | Initializes the window and main loop. |
| `src/core/game.c` | Core | Implements the slot machine. |
| `src/core/game.h` | Header | Declares functions, enums, and externs. |
| `src/config/config.h` | Configuration | Window, FPS, and economy constants. |

### Production Assets

| Directory | Content | Required |
| --------- | ------- | -------- |
| `assets/sprites/` | Machine and final symbols. | Yes |
| `assets/sprites/animation/` | 10 reel animation frames. | Yes |
| `assets/audio/` | Roulette and game-over MP3 sounds. | Yes for the full experience |

### Package Managers

The project does not use `npm`, `pip`, `vcpkg`, or another project-specific package manager. The main dependency is raylib installed on the system and discovered by CMake.

---

## Suggested Hardware

### Local Development

| Resource | Minimum | Recommended |
| -------- | ------- | ----------- |
| **RAM** | 2 GB | 4 GB or more |
| **CPU** | 1 core | 2 cores or more |
| **Disk** | 200 MB for project and build | 1 GB free if compiling raylib locally |
| **GPU** | Basic OpenGL support | Updated graphics driver |
| **OS** | Linux, macOS, or Windows with C toolchain | Linux with raylib installed |

### Game Runtime

| Resource | Note |
| -------- | ---- |
| **Window** | 400 x 400 pixels. |
| **Target FPS** | 40 FPS via `DEFAULT_FPS`. |
| **Audio** | Working audio device for MP3 playback. |
| **Input** | Mouse for spinning and restarting. |

### Ports Used

The project uses no network ports. The application is a local desktop game with no HTTP server, database, or external communication.
