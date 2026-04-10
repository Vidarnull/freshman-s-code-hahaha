#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   // 用于 _kbhit(), _getch()
#include <windows.h> // 用于 Sleep()

// --- 宏定义 ---
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_WORDS_ON_SCREEN 10 // 屏幕上同时存在的最大单词数
#define FILE_NAME "top10_scores.txt"

// --- 单词库 ---
const char *WORD_BANK[] = {
    "cat", "dog", "sky", "red", "blue", 
    "code", "java", "ruby", "perl", "unix",
    "linux", "apple", "hello", "world", "pixel",
    "pointer", "struct", "system", "memory", "random"
};
const int WORD_BANK_SIZE = 20;

// --- 结构体定义 ---
// 1. 用于表示屏幕上正在掉落的一个单词
typedef struct {
    char text[20];       // 单词内容
    int x;               // 横坐标 (列)
    int y;               // 纵坐标 (行)
    int length;          // 单词长度
    int typedIndex;      // 当前已经打对了几个字母
    int active;          // 是否激活 (1为正在掉落，0为空闲)
    int speedCounter;    // 用于控制不同单词的下落节奏
} Word;

// 2. 用于排行榜
typedef struct {
    char name[20];
    int score;
} Record;

// --- 全局变量 ---
Word activeWords[MAX_WORDS_ON_SCREEN]; // 结构体数组：管理屏幕上的单词
char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; // 屏幕缓冲区 (题目要求的二维数组)
int score = 0;
int gameLevel = 1;
int fallSpeedDelay = 200; // 游戏循环延迟 (毫秒)，越小越快
int gameOver = 0;

// --- 函数声明 ---
void initGame();
void drawScreen();
void updateGame();
void handleInput();
void spawnWord();
void saveScore(int finalScore);
void showLeaderboard();

int main() {
    // 随机数种子
    srand((unsigned int)time(NULL));

    // 显示排行榜
    showLeaderboard();
    printf("\n按任意键开始游戏...\n");
    _getch();

    initGame();

    // --- 游戏主循环 ---
    while (!gameOver) {
        drawScreen();   // 1. 画图
        handleInput();  // 2. 处理按键
        updateGame();   // 3. 更新逻辑 (移动、生成、判定)
        Sleep(fallSpeedDelay); // 4. 延时
    }

    // 游戏结束
    system("cls");
    printf("\n\n\n");
    printf("=============================\n");
    printf("      GAME OVER!             \n");
    printf("      最终得分: %d          \n", score);
    printf("=============================\n");
    
    // 保存分数
    saveScore(score);

    printf("\n按任意键退出...\n");
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
    
    // 初始化所有单词槽位为非激活状态
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        activeWords[i].active = 0;
    }
}

// 核心：生成一个新单词
void spawnWord() {
    // 1. 寻找一个空闲的结构体槽位
    int slot = -1;
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        if (activeWords[i].active == 0) {
            slot = i;
            break;
        }
    }

    // 如果没有空位，或者当前屏幕单词数已达难度上限，就不生成
    int maxWordsAllowed = 1 + (gameLevel / 2); // 难度控制：等级越高，允许同时存在的单词越多
    if (maxWordsAllowed > MAX_WORDS_ON_SCREEN) maxWordsAllowed = MAX_WORDS_ON_SCREEN;
    
    // 统计当前屏幕有多少个单词
    int currentCount = 0;
    for(int i=0; i<MAX_WORDS_ON_SCREEN; i++) if(activeWords[i].active) currentCount++;

    if (slot != -1 && currentCount < maxWordsAllowed) {
        // 生成新单词
        int wordIdx = rand() % WORD_BANK_SIZE;
        // 难度控制：等级高时，尝试随机更长的单词(简单的模拟)
        if (gameLevel > 5) {
             wordIdx = 10 + rand() % (WORD_BANK_SIZE - 10); // 偏向后半部分较长的词
        }

        strcpy(activeWords[slot].text, WORD_BANK[wordIdx]);
        activeWords[slot].length = strlen(activeWords[slot].text);
        activeWords[slot].x = rand() % (SCREEN_WIDTH - 15); // 随机X位置，留出边距
        activeWords[slot].y = 0; // 从顶端落下
        activeWords[slot].typedIndex = 0; // 还没打任何字母
        activeWords[slot].active = 1;
        activeWords[slot].speedCounter = 0;
    }
}

// 将数据渲染到二维数组，然后打印
void drawScreen() {
    // 1. 清空缓冲区 (填充空格)
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screenBuffer[i][j] = ' ';
        }
        screenBuffer[i][SCREEN_WIDTH] = '\0'; // 字符串结束符
    }

    // 2. 将单词填入缓冲区
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        // 使用指针指向当前处理的单词，方便操作
        Word *w = &activeWords[i]; 

        if (w->active) {
            int drawY = w->y;
            if (drawY >= 0 && drawY < SCREEN_HEIGHT) {
                // 将单词每个字符写入二维数组
                for (int k = 0; k < w->length; k++) {
                    int drawX = w->x + k;
                    if (drawX < SCREEN_WIDTH) {
                        // 如果这个字母已经被打对了，改成下划线或者大写提示
                        if (k < w->typedIndex) {
                            screenBuffer[drawY][drawX] = '_'; // 已打过的变成下划线
                        } else {
                            screenBuffer[drawY][drawX] = w->text[k];
                        }
                    }
                }
            }
        }
    }

    // 3. 绘制到底部状态栏
    // 使用 sprintf 直接格式化到底部的一行
    sprintf(screenBuffer[SCREEN_HEIGHT-1], " 分数: %d | 等级: %d | 难度延迟: %dms (按键打字)", score, gameLevel, fallSpeedDelay);

    // 4. 刷新屏幕 (system cls + printf)
    system("cls"); // 清屏
    
    // 一次性打印所有行
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]);
    }
}

// 处理用户输入
void handleInput() {
    if (_kbhit()) { // 检测是否有键盘按下
        char ch = _getch(); // 读取按键
        
        // 遍历所有活动的单词，检查匹配
        for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
            Word *w = &activeWords[i];
            
            if (w->active) {
                // 获取该单词当前需要打的字母
                char targetChar = w->text[w->typedIndex];
                
                if (ch == targetChar) {
                    w->typedIndex++; // 匹配成功，指向下一个字母
                    
                    // 检查是否整个单词打完了
                    if (w->typedIndex >= w->length) {
                        w->active = 0; // 销毁单词
                        score += 10;   // 加分
                        
                        // 难度升级逻辑
                        if (score % 50 == 0) {
                            gameLevel++;
                            if (fallSpeedDelay > 50) fallSpeedDelay -= 10; // 速度变快
                        }
                    }
                    // 简单的逻辑：一次按键只匹配第一个符合条件的单词，避免一键双雕
                    break; 
                }
            }
        }
    }
}

// 游戏逻辑更新：移动单词，判断生死
void updateGame() {
    static int spawnTimer = 0;
    spawnTimer++;

    // 1. 定期生成新单词
    // 难度控制：等级越高，生成频率越快
    int spawnRate = 15 - gameLevel; 
    if (spawnRate < 2) spawnRate = 2;
    
    if (spawnTimer % spawnRate == 0) {
        spawnWord();
    }

    // 2. 移动所有单词
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i];
        if (w->active) {
            w->y++; // 向下移动一格
            
            // 3. 落地判定 (游戏结束)
            if (w->y >= SCREEN_HEIGHT - 1) { // 减1是因为最后一行是状态栏
                gameOver = 1;
            }
        }
    }
}

// 保存分数并处理 Top 10
void saveScore(int finalScore) {
    Record records[11]; // 多留一个位置给当前分数
    int count = 0;
    FILE *fp = fopen(FILE_NAME, "r");

    // 1. 读取历史记录
    if (fp != NULL) {
        while (count < 10 && fscanf(fp, "%s %d", records[count].name, &records[count].score) == 2) {
            count++;
        }
        fclose(fp);
    }

    // 2. 添加当前用户的分数
    printf("\n请输入你的名字: ");
    scanf("%s", records[count].name);
    records[count].score = finalScore;
    count++;

    // 3. 排序 (冒泡排序，按分数从大到小)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (records[j].score < records[j+1].score) {
                Record temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
            }
        }
    }

    // 4. 写入前10名回文件
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("无法保存分数文件！\n");
        return;
    }
    
    int saveCount = count < 10 ? count : 10;
    printf("\n--- 最新 TOP 10 ---\n");
    for (int i = 0; i < saveCount; i++) {
        fprintf(fp, "%s %d\n", records[i].name, records[i].score);
        printf("第%d名: %s \t %d分\n", i+1, records[i].name, records[i].score);
    }
    fclose(fp);
    printf("记录已保存。\n");
}

// 显示排行榜
void showLeaderboard() {
    FILE *fp = fopen(FILE_NAME, "r");
    char name[20];
    int s;
    printf("=============================\n");
    printf("       历史最高分 TOP 10     \n");
    printf("=============================\n");
    if (fp == NULL) {
        printf("暂无记录。\n");
    } else {
        int i = 1;
        while (fscanf(fp, "%s %d", name, &s) == 2) {
            printf("%d. %s \t %d\n", i++, name, s);
        }
        fclose(fp);
    }
    printf("=============================\n");
}