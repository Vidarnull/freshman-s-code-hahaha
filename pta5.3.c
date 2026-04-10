#include <stdio.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    int odd = 0, even = 0;
    for (int i = 0; i < N; ++i) {
        long long x;
        if (scanf("%lld", &x) != 1) break;
        if (x % 2 == 0) ++even;
        else ++odd;
    }
    // 输出格式：先奇数个数，再偶数个数，用空格分隔
    printf("%d %d\n", odd, even);
    return 0;
}

























                               