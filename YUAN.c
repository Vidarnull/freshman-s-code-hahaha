#include <stdio.h>

#define PI 3.14159  // 用宏定义标识符代表常量 π

int main() {
    double radius, circumference, area;

    // 输入半径
    printf("请输入圆的半径：");
    scanf("%lf", &radius);

    // 计算圆周长和面积
    circumference = 2 * PI * radius;
    area = PI * radius * radius;

    // 输出结果
    printf("半径 = %.2f\n", radius);
    printf("圆周长 = %.2f\n", circumference);
    printf("圆面积 = %.2f\n", area);

    return 0;
}