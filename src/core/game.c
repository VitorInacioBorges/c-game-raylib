#include "raylib.h"
#include "../config/config.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>

SlotState slot_state;
int money;
int reels[3];
float spinTimer;

void InitGame(){
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

void DrawGame(){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello My Friend!", 50, 325, 20, BLACK);
    EndDrawing();
}

void StartSpin(){

}

void UpdateGame(){

}