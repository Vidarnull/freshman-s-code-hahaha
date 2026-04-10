#include <stdio.h>
#include <math.h>

/**
 * 计算三角形面积的函数
 * 参数：三条边长 a, b, c
 * 返回值：面积（若边长不合法则返回 -1）
 */
double calcTriangleArea(double a, double b, double c) {
    // 判断能否构成三角形
    if (a <= 0 || b <= 0 || c <= 0 || 
        a + b <= c || a + c <= b || b + c <= a) {
        return -1;  // 返回-1表示边长无效
    }
    
    // 海伦公式
    double p = (a + b + c) / 2;  // 半周长
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}

int main() {
    double a, b, c;
    
    // 输入三条边长
    printf("请输入三角形的三条边长：");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    // 调用函数计算面积
    double area = calcTriangleArea(a, b, c);
    
    // 输出结果
    if (area >= 0) {
        printf("三角形面积为：%.2f\n", area);
    } else {
        printf("输入的三条边长无法构成有效三角形。\n");
    }
    
    return 0;
}