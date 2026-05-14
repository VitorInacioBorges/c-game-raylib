# Best Practices

## Design Principles

### Single Responsibility

Each file has a clear responsibility:

- **`main.c`**: raylib application lifecycle.
- **`config.h`**: Configuration and balancing constants.
- **`game.h`**: Public contract for the game module.
- **`game.c`**: Rules, states, animation, drawing, and interaction.
- **`assets/`**: External resources used at runtime.

### Practical Low Coupling

The game is naturally coupled to raylib, but that coupling is concentrated in `main.c` and `game.c`. Numeric configuration is isolated in `config.h`.

### Clarity Around Global State

The project uses global variables for game state. In a small game, this makes reading and learning easier. In a larger game, it would be better to group this state into a `Game` struct and pass it to functions.

---

## Error Handling

### Assets

| Situation | Current state | Recommended best practice |
| --------- | ------------- | ------------------------- |
| Missing sprite | `LoadTexture()` is called without explicit checks. | Check `texture.id` after loading and exit with a clear message if it fails. |
| Missing sound | `LoadSound()` is called without explicit checks. | Validate the loaded resource and avoid `PlaySound()` on invalid resources. |
| Wrong relative path | The code expects execution from `build/`. | Document the correct execution directory or resolve paths from the executable location. |

### Runtime

| Layer | Current strategy |
| ----- | ---------------- |
| **Input** | Only left mouse click starts a spin and confirms the result. |
| **Game Over** | Separate state with a `TRY AGAIN` button to reset balance and state. |
| **Timers** | Reduced with `GetFrameTime()` and used for spin, loss message, and shake. |

---

## Testing

### Configured Test Types

| Type | Framework | Configuration |
| ---- | --------- | ------------- |
| **Automated** | Not configured | There is no versioned test suite in the current project. |
| **Build** | CMake + C compiler | `cmake -S . -B build` and `cmake --build build`. |
| **Manual** | Game execution | Open `build/game`, click to spin, validate win, loss, and game over. |

### Manual Checklist

```text
1. Build without errors.
2. Run from build/.
3. Confirm the 400 x 400 window opens.
4. Confirm clicking starts the spin and plays roleta.mp3.
5. Confirm the animation appears during the spin.
6. Confirm winning increases money.
7. Confirm losing shows PERDEU!! and applies shake.
8. Confirm zero balance leads to GAME_OVER.
9. Confirm TRY AGAIN resets the game.
```

### Coverage

No coverage collection is configured. To evolve the project, pure rule functions, such as win calculation and balance updates, could be extracted to make C unit tests easier.

---

## Security

### Security Surface

The game has no networking, authentication, database, user files, or secret variables. Its security surface is low and limited to loading local files.

| Aspect | Implementation |
| ------ | -------------- |
| **Secrets** | No versioned secrets. |
| **External input** | Only mouse input and window close. |
| **Loaded files** | PNG and MP3 files from relative paths inside `assets/`. |
| **Persisted data** | No data persisted between runs. |

### Local File Management

`.gitignore` ignores artifacts and local directories:

```text
build
raylib
.agent
.agents
.codex
```

This avoids versioning binaries, local builds, a local raylib checkout, and agent files.

---

## Known Technical Risks

| Risk | Impact | Recommendation |
| ---- | ------ | -------------- |
| `main.c` includes `game.c` directly | Can confuse maintenance and cause duplication if `game.c` is added to the build separately. | Compile `src/core/game.c` through CMake and include only `game.h` in `main.c`. |
| Assets use `../assets/...` | Running from another directory can break asset loading. | Standardize execution from `build/` or resolve an absolute path at startup. |
| Animation frames are not explicitly unloaded | Texture leak on shutdown, small in the current project. | Create `UnloadGame()` to release animation textures and loaded sounds. |
| `grito.mp3` is unused | Versioned asset with no code reference. | Remove if unnecessary or integrate into a gameplay event. |
| No automated tests | Rule regressions may go unnoticed. | Extract pure rules and add unit tests. |
