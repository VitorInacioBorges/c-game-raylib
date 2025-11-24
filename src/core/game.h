#ifndef GAME_H

#define GAME_H
#define FRUITS 3

typedef enum {
    SLOT_STATIC,     
    SLOT_SPINNING,  
    SLOT_RESULT,  
} SlotState;

typedef enum {
    GAMEPLAY,
    GAME_OVER
} GameState;

void InitGame();
void UpdateGame();
void DrawFruit(int fruit, int x, int y, int offsetX, int offsetY);
void DrawGameOver();
void DrawGame();
void InitAnimation(int i, const char *path, int frameCount, float frameTime, float delay);
void UpdateAnimation();
void DrawAnimation(int i, int x, int y);
void StartSpin();
void WinGame();
void LoseGame();

extern SlotState slot_state;
extern int money;
extern int reels[3];
extern int game_over;
extern float spin_timer;
extern float shake_timer;
extern float lose_message_timer;

#endif