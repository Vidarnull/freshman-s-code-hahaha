#include <stdio.h>
#include <math.h>  // 提供 exp 函数

int main() {
    int n, i;
    double x, s = 0.0;  // s 用于累加和

    // 输入 n 和 x
    printf("请输入 n（正整数）: ");
    scanf("%d", &n);
    printf("请输入 x（实数）: ");
    scanf("%lf", &x);

    // 计算累加和：s = e^x + e^(2x) + ... + e^(n*x)
    for (i = 1; i <= n; i++) {
        s += exp(i * x);  // 等价于 s = s + exp(i*x)
    }

    // 输出结果
    printf("e^(%g) + e^(%g) + ... + e^(%d*%g) = %g\n", 
           x, 2*x, n, x, s);
    
    return 0;
}