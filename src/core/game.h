#ifndef GAME_H

#define GAME_H
#define FRUITS 3

typedef enum {
    SLOT_STATIC,     
    SLOT_SPINNING,  
    SLOT_RESULT     
} SlotState;

void InitGame();
void UpdateGame();
void DrawFruit(int fruit, int x, int y, int offsetX, int offsetY);
void DrawGame();
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