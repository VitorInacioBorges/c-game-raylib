// codigo teste para abrir a janela

#include "raylib.h"
#include "./config/config.h"
#include "./core/game.h"

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}