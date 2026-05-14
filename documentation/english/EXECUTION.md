# Execution Guide

## Local Setup

### 1. Clone the Repository

```bash
git clone git@github.com:YOUR_USER/c-game-raylib.git
cd c-game-raylib
```

### 2. Install System Dependencies

Example for Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential git cmake
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev
sudo apt install libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev
sudo apt install libxinerama-dev libwayland-dev libxkbcommon-dev
```

### 3. Install raylib

If your distribution provides a development package:

```bash
sudo apt install libraylib-dev
```

If the package is not available, build raylib from source and install it system-wide:

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir -p build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
sudo cmake --install .
sudo ldconfig
```

### 4. Build with CMake

Run from the project root:

```bash
cmake -S . -B build
cmake --build build
```

The expected executable is:

```bash
build/game
```

### 5. Run the Game

Run from the `build/` directory because the code loads assets with relative `../assets/...` paths:

```bash
cd build
./game
```

---

## Available Scripts

### CMake

| Command | Description |
| ------- | ----------- |
| `cmake -S . -B build` | Configures the project and generates build files in `build/`. |
| `cmake --build build` | Compiles the `game` executable. |
| `cd build && ./game` | Runs the game with correct asset paths. |

### VS Code (`.vscode/tasks.json`)

| Task | Command | Description |
| ---- | ------- | ----------- |
| `C/C++: gcc build active file` | `/usr/bin/gcc ${file} ... -lraylib ...` | Compiles the active file with raylib and Linux library link flags. |

> The VS Code task is useful for local study, but the documented main project flow is CMake.

---

## Build Workflow

### Clean Build

```bash
cmake -S . -B build
cmake --build build
```

### Rebuild after Changes

```bash
cmake --build build
```

### Clean Artifacts

`build/` is ignored by Git. To rebuild everything from scratch, remove the folder manually and configure again:

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

---

## Distribution Strategy

### Local Build

The project is structured for local use. The `build/game` binary depends on:

- raylib available on the system;
- platform graphics/audio libraries;
- the `assets/` folder preserved at the expected relative path.

### Manual Packaging

To distribute manually, preserve the relationship between binary and assets:

```bash
release/
├── game
└── assets/
    ├── audio/
    └── sprites/
```

In that format, the code paths would need to change from `../assets/...` to `./assets/...`, or the binary would need to stay in a subdirectory equivalent to `build/`.

---

## Healthchecks

### Check Toolchain

```bash
cc --version
cmake --version
```

### Check CMake Configuration

```bash
cmake -S . -B build
```

Expected result: CMake finds raylib and generates build files without error.

### Check Build

```bash
cmake --build build
```

Expected result: `build/game` executable is generated.

### Check Runtime

```bash
cd build
./game
```

Expected result:

```text
1. "Slot Machine Game" window opens at 400 x 400.
2. Machine is rendered in the center.
3. Left click starts the spin and plays the roulette sound.
4. Reels animate and then display final symbols.
5. Balance changes according to win or loss.
6. With zero balance, game over appears and TRY AGAIN resets the game.
```

---

## Routine Execution

Checklist for local development:

```bash
# 1. Enter the project
cd c-game-raylib

# 2. Configure build, if it does not exist yet
cmake -S . -B build

# 3. Compile
cmake --build build

# 4. Run with correct asset paths
cd build
./game
```
