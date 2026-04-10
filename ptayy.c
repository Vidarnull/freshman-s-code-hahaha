#include <stdio.h>

int main() {
    int x, y;
    scanf("%d %d", &x, &y);           // 读取输入的 x 和 y
    int A = 5000 - 10 * (x + y);      // 按公式计算心理阴影面积
    printf("%d\n", A);                // 输出结果
    return 0;
}