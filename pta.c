#include <stdio.h>

int main() {
    int A, B;
    
    // 读取两个正整数A和B
    scanf("%d %d", &A, &B);
    
    // 按照要求格式输出五种运算结果
    printf("%d + %d = %d\n", A, B, A + B);      // 加法
    printf("%d - %d = %d\n", A, B, A - B);      // 减法
    printf("%d * %d = %d\n", A, B, A * B);      // 乘法
    printf("%d / %d = %d\n", A, B, A / B);      // 除法（整数商）
    printf("%d %% %d = %d\n", A, B, A % B);     // 取余
    
    return 0;
}