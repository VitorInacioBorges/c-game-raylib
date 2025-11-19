#include "raylib.h"

void DrawGame(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Raylib funcionando!", 190, 280, 20, DARKGRAY);
    EndDrawing();
}