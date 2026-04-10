#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   // for _kbhit(), _getch()
#include <windows.h> // for Sleep()
// --- 宏定义 ---
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_WORDS_ON_SCREEN 10 // 屏幕上同时显示的最大单词数

// --- 单词库 ---
const char *WORD_BANK[] = {
    "cat", "dog", "sky", "red", "blue", 
    "code", "java", "ruby", "perl", "unix",
    "linux", "apple", "hello", "world", "pixel",
    "pointer", "struct", "system", "memory", "random"
};
const int WORD_BANK_SIZE = 20;

// --- 结构体定义 ---
// 表示屏幕上正在下落的单词
typedef struct {
    char text[20];       // 单词内容
    int x;               // X坐标 (列)
    int y;               // Y坐标 (行)
    int length;          // 单词长度
    int typedIndex;      // 已正确输入的字母数
    int active;          // 是否处于活动状态 (1 = 下落中, 0 = 非活动)
    int speedCounter;    // 控制下落节奏
} Word;

// --- 全局变量 ---
Word activeWords[MAX_WORDS_ON_SCREEN]; // 管理屏幕上单词的数组
char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; // 屏幕缓冲区
int score = 0;
int gameLevel = 1;
int fallSpeedDelay = 200; // 游戏循环延迟 (毫秒)
int gameOver = 0;

// --- 函数声明 ---
void initGame();
void drawScreen();
void updateGame();
void handleInput();
void spawnWord();

int main() {
    // 随机种子
    srand((unsigned int)time(NULL));

    printf("\nPress any key to start game...\n");
    _getch();

    initGame();

    // --- 主游戏循环 ---
    while (!gameOver) {
        drawScreen();   // 1. 绘制屏幕
        handleInput();  // 2. 处理输入
        updateGame();   // 3. 更新游戏逻辑
        Sleep(fallSpeedDelay); // 4. 延迟
    }

    // 游戏结束
    system("cls");
    printf("\n\n\n");
    printf("=============================\n");
    printf("         GAME OVER!         \n");
    printf("      Final Score: %d       \n", score);
    printf("=============================\n");
    
    printf("\nPress any key to exit...\n");
    _getch();
    return 0;
}

// --- 函数实现 ---

// 初始化游戏数据
void initGame() {
    score = 0;
    gameLevel = 1;
    fallSpeedDelay = 200;
    gameOver = 0;
    
    // 将所有单词槽初始化为非活动状态
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        activeWords[i].active = 0;
    }
}

// 核心功能: 生成新单词
void spawnWord() {
    // 查找可用的槽位
    int slot = -1;
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        if (activeWords[i].active == 0) {
            slot = i;
            break;
        }
    }

    // 如果没有可用槽位，或达到难度允许的最大单词数
    int maxWordsAllowed = 1 + (gameLevel / 2);
    if (maxWordsAllowed > MAX_WORDS_ON_SCREEN) maxWordsAllowed = MAX_WORDS_ON_SCREEN;
    
    // 计算当前活动单词数量
    int currentCount = 0;
    for(int i=0; i<MAX_WORDS_ON_SCREEN; i++) if(activeWords[i].active) currentCount++;

    if (slot != -1 && currentCount < maxWordsAllowed) {
        // 生成新单词
        int wordIdx = rand() % WORD_BANK_SIZE;
        // 难度设置: 更高等级获得更长的单词
        if (gameLevel > 5) {
             wordIdx = 10 + rand() % (WORD_BANK_SIZE - 10);
        }

        strcpy(activeWords[slot].text, WORD_BANK[wordIdx]);
        activeWords[slot].length = strlen(activeWords[slot].text);
        activeWords[slot].x = rand() % (SCREEN_WIDTH - 15); // 随机X位置
        activeWords[slot].y = 0; // 从顶部开始
        activeWords[slot].typedIndex = 0; // 尚未输入任何字母
        activeWords[slot].active = 1;
        activeWords[slot].speedCounter = 0;
    }
}

// 将数据渲染到二维数组，然后打印
void drawScreen() {
    // 清空缓冲区 (用空格填充)
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screenBuffer[i][j] = ' ';
        }
        screenBuffer[i][SCREEN_WIDTH] = '\0'; // 字符串终止符
    }

    // 用单词填充缓冲区
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i]; 

        if (w->active) {
            int drawY = w->y;
            if (drawY >= 0 && drawY < SCREEN_HEIGHT) {
                // 将每个字符写入二维数组
                for (int k = 0; k < w->length; k++) {
                    int drawX = w->x + k;
                    if (drawX < SCREEN_WIDTH) {
                        // 将正确输入的字母改为下划线
                        if (k < w->typedIndex) {
                            screenBuffer[drawY][drawX] = '_';
                        } else {
                            screenBuffer[drawY][drawX] = w->text[k];
                        }
                    }
                }
            }
        }
    }

    // 在底部绘制状态栏
    sprintf(screenBuffer[SCREEN_HEIGHT-1], " Score: %d | Level: %d | Speed: %dms (Type to play)", score, gameLevel, fallSpeedDelay);

    // 刷新屏幕
    system("cls");
    
    // 一次性打印所有行
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]);
    }
}

// 处理用户输入
void handleInput() {
    if (_kbhit()) { // 检查是否有按键按下
        char ch = _getch(); // 读取按键
        
        // 检查所有活动单词是否匹配
        for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
            Word *w = &activeWords[i];
            
            if (w->active) {
                // 获取当前目标字母
                char targetChar = w->text[w->typedIndex];
                
                if (ch == targetChar) {
                    w->typedIndex++; // 移动到下一个字母
                    
                    // 检查整个单词是否完成
                    if (w->typedIndex >= w->length) {
                        w->active = 0; // 移除单词
                        score += 10;   // 增加分数
                        
                        // 升级逻辑
                        if (score % 50 == 0) {
                            gameLevel++;
                            if (fallSpeedDelay > 50) fallSpeedDelay -= 10; // 提高速度
                        }
                    }
                    // 每次按键只匹配第一个符合条件的单词
                    break; 
                }
            }
        }
    }
}
