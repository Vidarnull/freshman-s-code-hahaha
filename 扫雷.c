#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main() {
    // 8个方向的偏移量
    int delta[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };
    
    int row, col, num;
    char map[10][10] = {0};   // 存储地雷和数字信息
    char show[10][10] = {0};  // 存储显示状态，1表示已翻开
    int totalMines = 10;      // 地雷总数
    
    // 初始化随机数生成器
    srand(time(0));
    
    // 初始化地图
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            map[row][col] = '0';  // 初始化为0，表示无地雷
        }
    }
    
    // 随机放置地雷
    num = 0;
    do {
        row = rand() % 10;
        col = rand() % 10;
        if (map[row][col] == '0') {  // 确保不在同一位置重复放置
            map[row][col] = 'x';     // 'x'表示地雷
            num++;
        }
    } while (num < totalMines);
    
    // 计算每个位置周围的地雷数
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            if (map[row][col] != 'x') {  // 如果不是地雷
                int cnt = 0;
                for (num = 0; num < 8; num++) {  // 检查8个方向
                    int newRow = row + delta[num][0];
                    int newCol = col + delta[num][1];
                    
                    // 检查是否在边界内
                    if (newRow < 0 || newRow >= 10 || newCol < 0 || newCol >= 10) {
                        continue;
                    }
                    
                    // 如果周围有地雷，计数加1
                    if (map[newRow][newCol] == 'x') {
                        cnt++;
                    }
                }
                map[row][col] = '0' + cnt;  // 存储周围地雷数
            }
        }
    }
    
    // 初始显示所有格子为*
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            printf("* ");
        }
        printf("\n");
    }
    
    int opened = 0;  // 已翻开的非地雷格子数
    int x, y;
    
    // 游戏主循环
    do {
        printf("请输入要翻开的坐标 (x y): ");
        scanf("%d %d", &x, &y);
        
        // 转换为数组索引（输入是1-10，数组是0-9）
        int realX = x - 1;
        int realY = y - 1;
        
        // 检查是否踩中地雷
        if (map[realX][realY] == 'x') {
            printf("游戏结束！你踩中了地雷！\n");
            
            // 显示所有地雷
            for (row = 0; row < 10; row++) {
                for (col = 0; col < 10; col++) {
                    printf("%c ", map[row][col]);
                }
                printf("\n");
            }
            return 0;
        }
        
        // 标记为已翻开
        if (show[realX][realY] == 0) {
            show[realX][realY] = 1;
            opened++;
        }
        
        // 清屏并显示当前游戏状态
        system("cls");
        printf("扫雷游戏:\n");
        for (row = 0; row < 10; row++) {
            for (col = 0; col < 10; col++) {
                if (show[row][col] == 1) {
                    printf("%c ", map[row][col]);  // 显示已翻开的格子
                } else {
                    printf("* ");  // 未翻开的格子显示*
                }
            }
            printf("\n");
        }
        
        printf("已翻开: %d\n", opened);
        
    } while (opened < 100 - totalMines);  // 直到翻开所有非地雷格子
    
    printf("恭喜你，获胜了！\n");
    return 0;
}

