// codigo teste para abrir a janela

#include "raylib.h"

int main(void)
{
    InitWindow(650, 650, "Slot Machine Game");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib funcionando!", 190, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}