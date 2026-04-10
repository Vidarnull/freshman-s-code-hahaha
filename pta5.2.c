#include <stdio.h>
#include <math.h>

int main(void) {
    double eps;
    if (scanf("%lf", &eps) != 1) return 0;
    if (eps < 0) eps = -eps; // 如果用户输负数，取绝对值，保持简单

    double sum = 0.0;
    int k = 0;
    int sign = 1; // k = 0 -> 正，k = 1 -> 负，以此类推

    while (1) {
        double term = sign * 1.0 / (1 + 3 * k); // 第 k 项为 (+/-)1/(1+3k)，从 k=0 开始
        sum += term;
        if (fabs(term) <= eps) break; // 当最后一项的绝对值不大于 eps 时停止（包含该项）
        sign = -sign;
        k++;
    }

    // 输出结果，保留 6 位小数，易于查看
    printf("%.6f\n", sum);
    return 0;
}
