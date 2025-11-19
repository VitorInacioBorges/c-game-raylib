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
void DrawGame();
void StartSpin();

extern SlotState slot_state;
extern int money;
extern int reels[3];
extern float spinTimer;

#endif