#include "raylib.h"
#include "./config/config.h"
#include "./core/game.c"

int main(void) {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(DEFAULT_FPS);
    InitGame();

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    UnloadSound(roulette_sound);
    UnloadSound(game_over_sound);

    UnloadTexture(slot_machine);
    UnloadTexture(fruit1);
    UnloadTexture(fruit2);
    UnloadTexture(fruit3);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}