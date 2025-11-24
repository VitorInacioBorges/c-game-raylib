#include "raylib.h"
#include "../config/config.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// criando a struct da animação aqui por que o game.h nao tem include de raylib

typedef struct {
    Texture2D texture[10];
    int frame_count;
    int current_frame;
    int frame_width;
    int frame_height;
    int active;
    float frame_time;
    float timer;
    float start_delay;
    float start_timer;
} Animation;

Animation animation[3];
SlotState slot_state;
GameState game_state;

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
    game_state = GAMEPLAY;

    reels[0] = rand() % FRUITS;
    reels[1] = rand() % FRUITS;
    reels[2] = rand() % FRUITS;

    spin_timer = 0;

    slot_machine = LoadTexture("../assets/sprites/slotMachine.png");
    fruit1       = LoadTexture("../assets/sprites/crucifix.png");
    fruit2       = LoadTexture("../assets/sprites/seven.png");
    fruit3       = LoadTexture("../assets/sprites/skull.png");

    roulette_sound  = LoadSound("../assets/audio/roleta.mp3");
    game_over_sound = LoadSound("../assets/audio/gameover.mp3");

    InitAnimation(0, "../assets/sprites/animation/mistery", 10, 0.10f, 0.0f);
    InitAnimation(1, "../assets/sprites/animation/mistery", 10, 0.10f, 0.3f);
    InitAnimation(2, "../assets/sprites/animation/mistery", 10, 0.10f, 0.6f);
}

void InitAnimation(int i, const char *path, int frame_count, float frame_time, float delay){
    animation[i].frame_count = frame_count;
    animation[i].current_frame = 0;
    animation[i].frame_time = frame_time;
    animation[i].timer = 0;
    animation[i].active = 1;
    animation[i].start_delay = delay;
    animation[i].start_timer = 0;

    for (int f = 1; f <= frame_count; f++) {
        char file[256];
        snprintf(file, sizeof(file), "%s%d.png", path, f);
        animation[i].texture[f-1] = LoadTexture(file);
    }
}

void UpdateAnimation(){
    for(int i = 0; i < 3; i++){
        if(!animation[i].active) continue;

        if (animation[i].start_timer < animation[i].start_delay) {
            animation[i].start_timer += GetFrameTime();
            continue;
        }

        animation[i].timer += GetFrameTime();

        if(animation[i].timer >= animation[i].frame_time){

            animation[i].timer = 0;
            animation[i].current_frame++;

            if(animation[i].current_frame >= animation[i].frame_count) {
                animation[i].current_frame = 0;
            }
        }
    }
}

void DrawAnimation(int i,int x, int y) {
    if (!animation[i].active) return;

    DrawTexture(animation[i].texture[ animation[i].current_frame ], x, y, WHITE);
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

void DrawGameOver() {

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("VOCÊ EMPOBRECEU!!", 70, 150, 25, RED);

    Rectangle btn = { 120, 200, 160, 50 };

    Color color = WHITE;

    if (CheckCollisionPointRec(GetMousePosition(), btn)) color = GRAY;

    DrawRectangleRec(btn, color);
    DrawText("TRY AGAIN", btn.x + 10, btn.y + 18, 25, BLACK);

    EndDrawing();

    // clique no botão
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), btn)) {

        game_over = 0;
        slot_state = SLOT_STATIC;
        money = INITIAL_MONEY;
        game_state = GAMEPLAY;  // reinicia tudo
    }
}

void DrawGame() {

    if (game_state == GAME_OVER) {
        DrawGameOver();
        return;
    }
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

    int slotX = mx + 130;
    int slotY = my + 123;
    int spacing = 55;
    
    if (slot_state != SLOT_SPINNING) {
        for (int i = 0; i < 3; i++) {
            DrawFruit(reels[i], slotX + i * spacing, slotY, shakeX, shakeY);
        }
    }

    if (slot_state == SLOT_SPINNING) {
        for (int i = 0; i < 3; i++) {
            DrawAnimation(i, slotX + i * spacing, slotY);
        }
    }

    DrawText(TextFormat("Dinheiro: %d", money), 20, 360, 25, WHITE);

    if (lose_message_timer > 0){
        DrawText("PERDEU!!", WINDOW_WIDTH/2 - 40, WINDOW_HEIGHT/2 + 120, 20, WHITE);
    }

    EndDrawing();
}

void WinGame() {
    money += GAIN_MONEY;
}

void LoseGame() {
    lose_message_timer = 1.0f;
    shake_timer = 0.40f;
}

void StartSpin() {
    if (money <= 0) return;

    money -= WITHDRAW_MONEY;
    slot_state = SLOT_SPINNING;
    spin_timer = 11.0f;
    
    for (int i = 0; i < 3; i++) {
        animation[i].active = 1;
        animation[i].current_frame = 0;
        animation[i].timer = 0;
        animation[i].start_timer = 0;
    }

    PlaySound(roulette_sound);
}

void UpdateGame() {

    if (game_state == GAME_OVER) return;

    UpdateAnimation();

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

                for (int i = 0; i < 3; i++) animation[i].active = 0;

                if (reels[0] == reels[1] && reels[1] == reels[2]){
                    WinGame();
                } else {
                    LoseGame();
                }
            } break;

        case SLOT_RESULT:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !game_over) {

                if (money <= 0) {
                    game_over = 1;
                    game_state = GAME_OVER;
                    PlaySound(game_over_sound);
                    break;
                }

                slot_state = SLOT_STATIC;
            } break;
    }
}