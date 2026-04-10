#include <stdio.h>

int main() {
    double num1, num2, sum;

    // 提示并输入第一个数
    printf("请输入第一个数：");
    scanf("%lf", &num1);

    // 提示并输入第二个数
    printf("请输入第二个数：");
    scanf("%lf", &num2);

    // 计算和
    sum = num1 + num2;

    // 输出结果
    printf("两数之和为：%.2f\n", sum);

    return 0;
}