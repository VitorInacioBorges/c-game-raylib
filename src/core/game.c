#include "raylib.h"
#include "../config/config.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>


SlotState slot_state;

int money;
int reels[3];
int game_over = 0;
float spin_timer;
float lose_message_timer = 0;
float shake_timer = 0;

Texture2D slot_machine;
Texture2D fruit1;
Texture2D fruit2;
Texture2D fruit3;

Sound roulette_sound;
Sound game_over_sound;
Sound scare_sound;


void InitGame() {

    srand(time(NULL));

    money = INITIAL_MONEY;
    slot_state = SLOT_STATIC;

    reels[0] = rand() % FRUITS;
    reels[1] = rand() % FRUITS;
    reels[2] = rand() % FRUITS;

    spin_timer = 0;

     /* Assets are located at ../assets relative to the build/ executable directory. 
         Use one level up ("..") because the binary is placed in the project's build/ folder. */
     slot_machine = LoadTexture("../assets/sprites/slotMachine.png");
     fruit1       = LoadTexture("../assets/sprites/crucifix.png");
     fruit2       = LoadTexture("../assets/sprites/seven.png");
     fruit3       = LoadTexture("../assets/sprites/skull.png");

     roulette_sound  = LoadSound("../assets/audio/roleta.mp3");
     game_over_sound = LoadSound("../assets/audio/gameover.mp3");
}

void DrawFruit(int fruit, int x, int y, int offsetX, int offsetY) {

    float scale = 1.f;

    switch (fruit) {
        case 0:
            DrawTextureEx(fruit1, (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
        case 1:
            DrawTextureEx(fruit2,  (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
        case 2:
            DrawTextureEx(fruit3,  (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
    }
}

void DrawGame() {

    BeginDrawing();

    ClearBackground(BLACK);

    int shakeX = 0;
    int shakeY = 0;

    if (shake_timer > 0) {
        shakeX = GetRandomValue(-4, 4);
        shakeY = GetRandomValue(-4, 4);
    }

    int mx = (WINDOW_WIDTH - slot_machine.width) / 2;
    int my = (WINDOW_HEIGHT - slot_machine.height) / 2;

    DrawTexture(slot_machine, mx + shakeX, my + shakeY, WHITE);

    int slotX = mx + 125;
    int slotY = my + 118;
    int spacing = 55;

    for (int i = 0; i < 3; i++) {
        DrawFruit(reels[i], slotX + i * spacing, slotY, shakeX, shakeY);
    }

    DrawText(TextFormat("Dinheiro: %d", money), 20, 20, 25, WHITE);

    if (lose_message_timer > 0){
        DrawText("PERDEU!!", WINDOW_WIDTH/2 - 40, WINDOW_HEIGHT/2 + 120, 20, WHITE);
    }
    if (game_over){
        DrawText("GAME OVER", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 - 160, 30, WHITE);
    }

    EndDrawing();
}

void WinGame() {
    money += 4000;
}

void LoseGame() {
    lose_message_timer = 1.0f;
    shake_timer = 0.40f;
}

void StartSpin() {
    if (money <= 0) return;

    money -= 500;
    slot_state = SLOT_SPINNING;
    spin_timer = 11.0f;

    PlaySound(roulette_sound);
}

void UpdateGame() {
    if (lose_message_timer > 0){
        lose_message_timer -= GetFrameTime();
    }
    if (shake_timer > 0){
        shake_timer -= GetFrameTime();
    }

    switch(slot_state){
        case SLOT_STATIC:
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                StartSpin();
            } break;

        case SLOT_SPINNING:
            spin_timer -= GetFrameTime();

            reels[0] = rand() % FRUITS;
            reels[1] = rand() % FRUITS;
            reels[2] = rand() % FRUITS;

            if(spin_timer <= 0) {
                slot_state = SLOT_RESULT;

                if (reels[0] == reels[1] && reels[1] == reels[2]){
                    WinGame();
                } else {
                    LoseGame();
                }
            } break;

        case SLOT_RESULT:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !game_over) {
                slot_state = SLOT_STATIC;
            }
            break;
    }
}