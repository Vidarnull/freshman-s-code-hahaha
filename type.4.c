#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 80
#define HEIGHT 25
#define MAX_WORDS 5

int score = 0;
int level = 1;
int speed = 500; // 初始下落速度（毫秒）
char words[][10] = {"apple", "hello", "world", "code", "test"};
int word_count = 5;

typedef struct {
    char text[10];
    int x;
    int y;
    int active;
} FallingWord;

FallingWord words_list[MAX_WORDS];

void init_game() {
    srand(time(NULL));
    score = 0;
    level = 1;
    speed = 500;
    for(int i=0; i<MAX_WORDS; i++) {
        words_list[i].active = 0;
    }
}

void draw_screen() {
    system("cls");
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            printf(" ");
        }
        printf("\n");
    }
    
    // 绘制单词
    for(int i=0; i<MAX_WORDS; i++) {
        if(words_list[i].active) {
            for(int j=0; j<strlen(words_list[i].text); j++) {
                printf("%c", words_list[i].text[j]);
            }
            printf("\n");
        }
    }
    
    // 绘制状态栏
    printf("\n\nScore: %d | Level: %d | Speed: %dms", score, level, speed);
}

void update_game() {
    static int time_counter = 0;
    time_counter++;
    
    // 生成新单词
    if(time_counter % (level*2) == 0) {
        for(int i=0; i<MAX_WORDS; i++) {
            if(!words_list[i].active) {
                int word_idx = rand() % word_count;
                strcpy(words_list[i].text, words[word_idx]);
                words_list[i].x = rand() % (WIDTH - strlen(words[word_idx]));
                words_list[i].y = 0;
                words_list[i].active = 1;
                break;
            }
        }
    }
    
    // 更新单词位置
    for(int i=0; i<MAX_WORDS; i++) {
        if(words_list[i].active) {
            words_list[i].y++;
            if(words_list[i].y >= HEIGHT) {
                printf("\nGame Over!");
                exit(0);
            }
        }
    }
}

void handle_input() {
    if(_kbhit()) {
        char c = _getch();
        for(int i=0; i<MAX_WORDS; i++) {
            if(words_list[i].active) {
                if(c == words_list[i].text[0]) {
                    printf("\nCorrect!");
                    score += 10;
                    words_list[i].active = 0;
                    level = (score / 50) + 1;
                    speed -= 50;
                    if(speed < 100) speed = 100;
                    break;
                }
            }
        }
    }
}

int main() {
    init_game();
    
    while(1) {
        draw_screen();
        update_game();
        handle_input();
        Sleep(speed);
    }
    
    return 0;
}