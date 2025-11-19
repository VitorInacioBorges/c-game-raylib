// codigo teste para abrir a janela

#include "raylib.h"
#include "./config/config.h"
#include "./core/game.c"

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    while (!WindowShouldClose()) {
        InitGame();
        DrawGame();
    }

    CloseWindow();
    return 0;
}