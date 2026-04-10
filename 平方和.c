#include <stdio.h>

int main() {
    double num1, num2, sum;

    // 输入两个数
    printf("请输入第一个数：");
    scanf("%lf", &num1);
    printf("请输入第二个数：");
    scanf("%lf", &num2);

    // 计算平方和
    sum = num1 * num1 + num2 * num2;

    // 输出结果
    printf("平方和为：%.2f\n", sum); // 保留两位小数
    return 0;
}