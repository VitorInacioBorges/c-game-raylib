#include "raylib.h"
#include "../config/config.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

SlotState slot_state;
int money;
int reels[3];
float spinTimer;

void InitGame() {
    // starts the random number generator
    srand(time(NULL));

    // sets the initial money and slot machine state
    money = INITIAL_MONEY;
    slot_state = SLOT_STATIC;

    reels[0] = rand() % FRUITS;
    reels[1] = rand() % FRUITS;
    reels[2] = rand() % FRUITS;

    spinTimer = 0;
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello My Friend!", 50, 325, 20, BLACK);
    EndDrawing();
}

void WinGame() {

}

void LoseGame() {

}

void StartSpin() {
    if (money <= 0) return;

    money -= 200;
    slot_state = SLOT_SPINNING;
    spinTimer = 1.2f;

    if (reels[0] == reels[1] && reels[1] == reels[2]){
        WinGame();
    } else {
        LoseGame();
    }
}

void UpdateGame() {
    switch(slot_state){
        case SLOT_STATIC:
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                StartSpin();
            } break;
        case SLOT_SPINNING:
        case SLOT_RESULT:
    }
}