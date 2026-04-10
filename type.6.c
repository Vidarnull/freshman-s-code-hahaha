/*
 * 程序名称：控制台打字练习游戏 (Falling Words)
 * 适合人群：C语言初学者 (大一)
 * 涉及知识点：结构体、数组、循环、随机数、函数封装、控制台输入输出
 * 注意事项：本程序使用了 <conio.h> 和 <windows.h>，因此只能在 Windows 系统下编译运行。
 */

#include <stdio.h>
#include <stdlib.h>     // 包含 rand(), srand(), system() 等通用工具函数
#include <string.h>     // 包含 strcpy(), strlen() 等字符串处理函数
#include <time.h>       // 包含 time()，用于生成随机数种子
#include <conio.h>      // 【Windows特有】用于 _kbhit() (检测按键) 和 _getch() (无回显读取字符)
#include <windows.h>    // 【Windows特有】用于 Sleep() 函数进行延时

// --- 宏定义 (常量的别名) ---
// 屏幕的宽和高，用于控制字符界面的大小
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
// 限制屏幕上同时出现的最大单词数量，防止太难
#define MAX_WORDS_ON_SCREEN 10 

// --- 单词库 ---
// 这是一个字符串数组，游戏会从这里随机挑选单词
const char *WORD_BANK[] = {
    "cat", "dog", "sky", "red", "blue", 
    "code", "java", "ruby", "perl", "unix",
    "linux", "apple", "hello", "world", "pixel",
    "pointer", "struct", "system", "memory", "random"
};
// 记录单词库里一共有多少个单词，方便计算随机数范围
const int WORD_BANK_SIZE = 20;

// --- 结构体定义 (核心数据结构) ---
// 我们定义一个新的类型叫 Word，用来描述屏幕上每一个正在下落的单词
typedef struct {
    char text[20];       // 存储单词本身的字符串，比如 "hello"
    int x;               // 单词在屏幕上的横坐标 (列)
    int y;               // 单词在屏幕上的纵坐标 (行)
    int length;          // 单词的长度，避免重复计算
    int typedIndex;      // 玩家已经打对了几个字母？(例如 "hello" 打了 'h'，这里就是1)
    int active;          // 开关标记：1代表这个单词正在屏幕上掉落，0代表这个槽位是空的
    int speedCounter;    // (预留变量) 用于未来扩展不同单词有不同速度
} Word;

// --- 全局变量 (整个程序都能访问的数据) ---
// 定义一个数组，最多管理 MAX_WORDS_ON_SCREEN 个单词对象
Word activeWords[MAX_WORDS_ON_SCREEN]; 

// 二维字符数组，相当于“显存”。我们先在内存里画好画面，再一次性打印出来，防止闪烁太严重
char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; 

int score = 0;           // 玩家得分
int gameLevel = 1;       // 当前关卡等级
int fallSpeedDelay = 200; // 游戏每一帧的延迟时间(毫秒)，数值越小，游戏运行越快
int gameOver = 0;        // 游戏结束标记：0=进行中，1=结束

// --- 函数声明 (告诉编译器有哪些功能模块) ---
void initGame();     // 初始化游戏数据
void drawScreen();   // 负责画图：把数据变成画面
void updateGame();   // 负责逻辑：移动单词、生成新单词
void handleInput();  // 负责输入：处理键盘按键
void spawnWord();    // 辅助功能：生成一个新单词

// --- 主函数 (程序的入口) ---
int main() {
    // 1. 设置随机数种子
    // 如果不写这行，每次运行游戏产生的单词顺序都是一模一样的
    srand((unsigned int)time(NULL));

    printf("\nPress any key to start game...\n");
    _getch(); // 等待用户按任意键继续

    // 2. 初始化游戏状态
    initGame();

    // 3. --- 游戏主循环 (Game Loop) ---
    // 这是所有游戏的核心：只要游戏没结束，就一直重复做“绘制->输入->更新->延时”
    while (!gameOver) {
        drawScreen();          // 步骤1：给玩家看当前的画面
        handleInput();         // 步骤2：看看玩家按键盘了吗？
        updateGame();          // 步骤3：计算单词的新位置、判断有没有输
        Sleep(fallSpeedDelay); // 步骤4：让程序暂停一下，控制游戏速度(FPS)
    }

    // 4. 游戏结束处理
    system("cls"); // 清屏
    printf("\n\n\n");
    printf("=============================\n");
    printf("         GAME OVER!         \n");
    printf("      Final Score: %d       \n", score);
    printf("=============================\n");
    
    printf("\nPress any key to exit...\n");
    _getch(); // 防止窗口直接关闭
    return 0;
}

// --- 函数具体实现 ---

// 功能：重置所有变量，开始新游戏
void initGame() {
    score = 0;
    gameLevel = 1;
    fallSpeedDelay = 200; // 初始速度
    gameOver = 0;
    
    // 遍历结构体数组，把所有单词槽位都标记为“非活动”(0)
    // 这样游戏刚开始时屏幕上是空的
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        activeWords[i].active = 0;
    }
}

// 功能：尝试在屏幕上生成一个新单词
void spawnWord() {
    // 1. 寻找空位：在数组里找一个 active 为 0 的位置
    int slot = -1;
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        if (activeWords[i].active == 0) {
            slot = i;
            break; // 找到一个空位就停止寻找
        }
    }

    // 2. 计算当前允许的最大单词数 (随等级增加，屏幕上单词变多)
    int maxWordsAllowed = 1 + (gameLevel / 2);
    // 封顶，不能超过数组总容量
    if (maxWordsAllowed > MAX_WORDS_ON_SCREEN) maxWordsAllowed = MAX_WORDS_ON_SCREEN;
    
    // 3. 统计当前屏幕上已经有多少个单词了
    int currentCount = 0;
    for(int i=0; i<MAX_WORDS_ON_SCREEN; i++) if(activeWords[i].active) currentCount++;

    // 4. 如果有空位 且 当前单词数还没达到上限，就生成新单词
    if (slot != -1 && currentCount < maxWordsAllowed) {
        // 从单词库随机选一个下标
        int wordIdx = rand() % WORD_BANK_SIZE;
        
        // 难度机制：如果等级超过5，只生成后10个单词(假设后10个更难)
        if (gameLevel > 5) {
             wordIdx = 10 + rand() % (WORD_BANK_SIZE - 10);
        }

        // --- 初始化这个新单词的数据 ---
        strcpy(activeWords[slot].text, WORD_BANK[wordIdx]); // 复制文字
        activeWords[slot].length = strlen(activeWords[slot].text); // 记下长度
        activeWords[slot].x = rand() % (SCREEN_WIDTH - 15); // x坐标随机，但在屏幕宽度内
        activeWords[slot].y = 0;          // y坐标为0，表示从最顶端出现
        activeWords[slot].typedIndex = 0; // 刚生成时，还没打过任何字母
        activeWords[slot].active = 1;     // 标记为活动状态，开始下落！
        activeWords[slot].speedCounter = 0;
    }
}

// 功能：渲染画面
// 原理：先在一个二维数组(缓冲区)里画好，再一次性打印，比直接打印更整洁
void drawScreen() {
    // 1. 清空缓冲区 (全部填上空格)
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screenBuffer[i][j] = ' ';
        }
        screenBuffer[i][SCREEN_WIDTH] = '\0'; // 每一行末尾加上字符串结束符
    }

    // 2. 把所有活动的单词“画”到缓冲区里
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i]; // 定义一个指针指向当前处理的单词，方便书写

        if (w->active) { // 只处理活动的单词
            int drawY = w->y;
            // 确保单词在屏幕高度范围内
            if (drawY >= 0 && drawY < SCREEN_HEIGHT) {
                // 遍历这个单词的每一个字母
                for (int k = 0; k < w->length; k++) {
                    int drawX = w->x + k;
                    // 确保字母在屏幕宽度范围内
                    if (drawX < SCREEN_WIDTH) {
                        // 核心视觉逻辑：
                        // 如果这个字母已经被打过了(索引 < typedIndex)，就显示为下划线 '_'
                        // 否则显示原本的字母
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

    // 3. 在缓冲区最后一行绘制状态栏 (分数、等级)
    sprintf(screenBuffer[SCREEN_HEIGHT-1], " Score: %d | Level: %d | Speed: %dms (Type to play)", score, gameLevel, fallSpeedDelay);

    // 4. 真正输出到控制台
    system("cls"); // 清除上一帧的画面 (注意：这里会产生轻微闪烁，是system("cls")的特性)
    
    // 逐行打印
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        printf("%s\n", screenBuffer[i]);
    }
}

// 功能：处理用户输入
void handleInput() {
    // _kbhit() 检查当前是否有键盘敲击，如果没有按键，直接跳过，不阻塞程序
    if (_kbhit()) { 
        char ch = _getch(); // 读取按下的键 (不会在屏幕上显示出来)
        
        // 遍历所有活动的单词，看看用户按的键是不是某个单词需要的
        for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
            Word *w = &activeWords[i];
            
            if (w->active) {
                // 获取这个单词当前需要打的字母
                // 例如单词是 "code"，typedIndex是1，那目标就是 'o'
                char targetChar = w->text[w->typedIndex];
                
                // 如果按键匹配
                if (ch == targetChar) {
                    w->typedIndex++; // 进度+1，指向下一个字母
                    
                    // 检查单词是否全部打完
                    if (w->typedIndex >= w->length) {
                        w->active = 0; // 标记为非活动，单词消失
                        score += 10;   // 加分
                        
                        // 升级逻辑：每得50分升一级
                        if (score % 50 == 0) {
                            gameLevel++;
                            // 速度加快 (延时减少)，但最快不低于50ms
                            if (fallSpeedDelay > 50) fallSpeedDelay -= 10; 
                        }
                    }
                    // 这里的 break 很重要：
                    // 如果屏幕上有两个单词都需要打 'a'，按一次键盘只消除最前面那个单词的 'a'
                    // 防止按一次键同时消除多个单词
                    break;
                }
            }
        }
    }
}

// 功能：更新游戏物理逻辑 (下落、生成)
void updateGame() {
    static int spawnTimer = 0; // 静态变量，函数结束后数值会保留，用于计时
    spawnTimer++;

    // 计算生成新单词的频率
    // Level 1: 15-1 = 14帧生成一个
    // Level 10: 15-10 = 5帧生成一个 (生成得更快)
    int spawnRate = 15 - gameLevel; 
    if (spawnRate < 2) spawnRate = 2; // 设个底线，不能太快
    
    // 计时器达到阈值，生成新单词
    if (spawnTimer % spawnRate == 0) {
        spawnWord();
    }

    // 移动所有活动的单词
    for (int i = 0; i < MAX_WORDS_ON_SCREEN; i++) {
        Word *w = &activeWords[i];
        if (w->active) {
            w->y++; // 坐标增加，视觉效果就是向下落
            
            // 碰撞检测：如果掉到了屏幕底部
            if (w->y >= SCREEN_HEIGHT - 1) { // 减1是为了避开底部的状态栏
                gameOver = 1; // 触发游戏结束
            }
        }
    }
}