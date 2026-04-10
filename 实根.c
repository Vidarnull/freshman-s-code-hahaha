#include <stdio.h>
#include <math.h>

/**
 * 计算一元二次方程 a·x² + b·x + c = 0 (a ≠ 0) 的两个实根
 * @param a  二次项系数（非零）
 * @param b  一次项系数
 * @param c  常数项
 * @param x1 指向第一个根的指针
 * @param x2 指向第二个根的指针
 * @return   根的类型：1表示两个不同实根，0表示两个相等实根，-1表示无实根（这里暂不处理）
 */
int solveQuadratic(double a, double b, double c, double *x1, double *x2) {
    if (a == 0) {
        printf("错误：a不能为0！\n");
        return -1;
    }
    
    double delta = b * b - 4 * a * c;  // 判别式 Δ = b² - 4ac
    
    if (delta < 0) {
        // 题目要求为实根，此处仅提示，实际应处理复数根
        printf("方程无实根（判别式小于0）\n");
        return -1;
    }
    
    // 计算两个根
    *x1 = (-b + sqrt(delta)) / (2 * a);
    *x2 = (-b - sqrt(delta)) / (2 * a);
    
    // 判断根的类型
    if (delta > 0) {
        return 1;  // 两个不同实根
    } else {
        // delta == 0 时两个根相等
        *x2 = *x1;  // 确保x2与x1相同（可选）
        return 0;   // 两个相等实根
    }
}

int main() {
    double a, b, c;
    double root1, root2;
    
    // 输入系数
    printf("求解一元二次方程 a·x² + b·x + c = 0\n");
    printf("请输入系数 a (非零), b, c：");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    // 调用函数计算
    int result = solveQuadratic(a, b, c, &root1, &root2);
    
    // 输出结果
    if (result == 1) {
        printf("两个不同实根：x1 = %.4f, x2 = %.4f\n", root1, root2);
    } else if (result == 0) {
        printf("两个相等实根：x = %.4f\n", root1);
    } else if (result == -1) {
        printf("方程无实根（或a=0）。\n");
    }
    
    return 0;
}