#include "raylib.h"
#include <stdlib.h>
#include <time.h>

// =============================
#define WINDOW_TITLE   "Slot Machine Game"
#define WINDOW_WIDTH   400
#define WINDOW_HEIGHT  400

#define INITIAL_MONEY  1000
#define DEFAULT_FPS    40
#define FRUITS 3
// =============================

typedef enum {
    SLOT_STATIC,
    SLOT_SPINNING,
    SLOT_RESULT
} SlotState;

SlotState slot_state;
int money;
int reels[3];
float spinTimer;

float loseMessageTimer = 0;
int gameOver = 0;

float shakeTimer = 0;

// Só um susto por jogo
int scareTriggered = 0;

// Texturas
Texture2D maquina;
Texture2D sprite_limao;
Texture2D sprite_uva;
Texture2D sprite_maca;

// Sons
Sound somRoleta;
Sound somGameOver;
Sound somSusto;

// =============================
//  FUNÇÃO DO SUSTO EM JANELA 1366x768
// =============================
void AbrirJanelaSusto() {

    // Fecha a janela atual do jogo
    CloseWindow();
    CloseAudioDevice();

    // Tamanho fixo da janela do susto
    int screenW = 1366;
    int screenH = 768;

    InitWindow(screenW, screenH, "!!! SUSTO !!!");

    InitAudioDevice();
    Sound grito = LoadSound("grito.mp3");
    Texture2D imagemSusto = LoadTexture("susto.jpg");

    PlaySound(grito);

    // Ajuste proporcional da imagem
    float scaleX = (float)screenW / imagemSusto.width;
    float scaleY = (float)screenH / imagemSusto.height;
    float scale = (scaleX > scaleY) ? scaleX : scaleY;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 pos = {
            (screenW - imagemSusto.width * scale) / 2,
            (screenH - imagemSusto.height * scale) / 2
        };

        DrawTextureEx(imagemSusto, pos, 0, scale, WHITE);

        EndDrawing();
    }

    UnloadSound(grito);
    UnloadTexture(imagemSusto);

    CloseAudioDevice();
    CloseWindow();

    // VOLTA ao jogo
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(DEFAULT_FPS);
}

// =============================
void InitGame() {
    srand(time(NULL));

    money = INITIAL_MONEY;
    slot_state = SLOT_STATIC;

    reels[0] = rand() % FRUITS;
    reels[1] = rand() % FRUITS;
    reels[2] = rand() % FRUITS;

    spinTimer = 0;

    maquina      = LoadTexture("maquina.png");
    sprite_limao = LoadTexture("caveira.png");
    sprite_uva   = LoadTexture("sete.png");
    sprite_maca  = LoadTexture("crucifixo.png");

    somRoleta   = LoadSound("roleta.mp3");
    somGameOver = LoadSound("gameover.mp3");

    scareTriggered = 0;
}

// =============================
void WinGame() {
    money += 400;
}

void LoseGame() {

    loseMessageTimer = 1.0f;
    shakeTimer = 0.40f;

    if (money <= 0 && !scareTriggered) {
        scareTriggered = 1;
        PlaySound(somGameOver);

        AbrirJanelaSusto();

        gameOver = 1;
    }
}

// =============================
void StartSpin() {
    if (money <= 0) return;

    money -= 200;
    slot_state = SLOT_SPINNING;
    spinTimer = 11.0f;

    PlaySound(somRoleta);
}

// =============================
void UpdateGame() {

    if (loseMessageTimer > 0)
        loseMessageTimer -= GetFrameTime();

    if (shakeTimer > 0)
        shakeTimer -= GetFrameTime();

    switch (slot_state) {

        case SLOT_STATIC:
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gameOver) {
                StartSpin();
            }
            break;

        case SLOT_SPINNING:
            spinTimer -= GetFrameTime();

            reels[0] = rand() % FRUITS;
            reels[1] = rand() % FRUITS;
            reels[2] = rand() % FRUITS;

            if (spinTimer <= 0) {
                slot_state = SLOT_RESULT;

                if (reels[0] == reels[1] && reels[1] == reels[2])
                    WinGame();
                else
                    LoseGame();
            }
            break;

        case SLOT_RESULT:
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gameOver) {
                slot_state = SLOT_STATIC;
            }
            break;
    }
}

// =============================
void DrawFruit(int fruit, int x, int y, int offsetX, int offsetY) {

    float scale = 1.f;

    switch (fruit) {
        case 0:
            DrawTextureEx(sprite_limao, (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
        case 1:
            DrawTextureEx(sprite_uva,   (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
        case 2:
            DrawTextureEx(sprite_maca,  (Vector2){x + offsetX, y + offsetY}, 0, scale, WHITE);
            break;
    }
}

// =============================
void DrawGame() {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    int shakeX = 0;
    int shakeY = 0;

    if (shakeTimer > 0) {
        shakeX = GetRandomValue(-4, 4);
        shakeY = GetRandomValue(-4, 4);
    }

    int mx = (WINDOW_WIDTH - maquina.width) / 2;
    int my = (WINDOW_HEIGHT - maquina.height) / 2;

    DrawTexture(maquina, mx + shakeX, my + shakeY, WHITE);

    int slotX = mx + 125;
    int slotY = my + 118;
    int spacing = 59;

    for (int i = 0; i < 3; i++)
        DrawFruit(reels[i], slotX + i * spacing, slotY, shakeX, shakeY);

    DrawText(TextFormat("Dinheiro: %d", money), 20, 20, 25, BLACK);

    if (loseMessageTimer > 0)
        DrawText("PERDEU!", WINDOW_WIDTH/2 - 40, WINDOW_HEIGHT/2 + 120, 20, RED);

    if (gameOver)
        DrawText("GAME OVER", WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 - 160, 30, RED);

    EndDrawing();
}

// =============================
int main(void) {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(DEFAULT_FPS);

    InitGame();

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }

    UnloadSound(somRoleta);
    UnloadSound(somGameOver);
    UnloadSound(somSusto);

    UnloadTexture(maquina);
    UnloadTexture(sprite_limao);
    UnloadTexture(sprite_uva);
    UnloadTexture(sprite_maca);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}