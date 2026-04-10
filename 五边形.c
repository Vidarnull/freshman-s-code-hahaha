#include <stdio.h>
#include <math.h>

// 海伦公式计算三角形面积
double triangleArea(double a, double b, double c) {
    double p = (a + b + c) / 2;  // 半周长
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    double a1, b1, c1;  // 三角形1的边长
    double a2, b2, c2;  // 三角形2的边长
    double a3, b3, c3;  // 三角形3的边长
    double area1, area2, area3, totalArea;

    // 输入第一个三角形的三边
    printf("请输入第一个三角形的三边长：");
    scanf("%lf %lf %lf", &a1, &b1, &c1);
    // 输入第二个三角形的三边
    printf("请输入第二个三角形的三边长：");
    scanf("%lf %lf %lf", &a2, &b2, &c2);
    // 输入第三个三角形的三边
    printf("请输入第三个三角形的三边长：");
    scanf("%lf %lf %lf", &a3, &b3, &c3);

    // 计算各三角形面积
    area1 = triangleArea(a1, b1, c1);
    area2 = triangleArea(a2, b2, c2);
    area3 = triangleArea(a3, b3, c3);
    totalArea = area1 + area2 + area3;

    // 输出结果
    printf("第一个三角形面积：%.2f\n", area1);
    printf("第二个三角形面积：%.2f\n", area2);
    printf("第三个三角形面积：%.2f\n", area3);
    printf("五边形总面积：%.2f\n", totalArea);

    return 0;
}