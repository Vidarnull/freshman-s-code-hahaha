#include "game_framework.h"

// 处理用户输入
void handleInput() {
    if (_kbhit()) {
        char ch = _getch();
        
        for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
            Word *w = &activeWords[i];
            
            if (w->active) {
                char targetChar = w->text[w->typedIndex];
                
                if (ch == targetChar) {
                    w->typedIndex++;
                    
                    if (w->typedIndex >= w->length) {
                        w->active = 0;
                        score += 10;
                        
                        if (score % 50 == 0) {
                            gameLevel++;
                            if (fallSpeedDelay > 50) fallSpeedDelay -= 10;
                        }
                    }
                    break;
                }
            }
        }
    }
}

// 更新游戏状态
void updateGame() {
    static int spawnTimer = 0;
    spawnTimer++;

    int spawnRate = 15 - gameLevel;
    if (spawnRate < 2) spawnRate = 2;
    
    if (spawnTimer % spawnRate == 0) {
        spawnWord();
    }

    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i];
        if (w->active) {
            w->y++;
            
            if (w->y >= SCREEN_HEIGHT - 1) {
                gameOver = 1;
            }
        }
    }
}