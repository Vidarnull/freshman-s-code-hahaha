#include <stdio.h>

// 递归函数：逆序输出整数的每一位数字
void reversePrint(int n) {
    // 如果 n 是负数，先输出负号并转为正数处理
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    
    // 递归终止条件：n 为个位数时直接输出
    if (n < 10) {
        printf("%d", n);
    } else {
        // 输出当前最低位（个位）
        printf("%d", n % 10);
        // 递归处理剩余高位部分
        reversePrint(n / 10);
    }
}

int main() {
    int num;
    
    // 输入整数
    printf("请输入一个整数：");
    scanf("%d", &num);
    
    // 调用递归函数逆序输出
    printf("逆序输出结果：");
    reversePrint(num);
    printf("\n");
    
    return 0;
}