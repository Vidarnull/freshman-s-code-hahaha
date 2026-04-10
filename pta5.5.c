#include <stdio.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    int A = 0, B = 0, C = 0, D = 0, E = 0;
    for (int i = 0; i < N; ++i) {
        int score;
        if (scanf("%d", &score) != 1) break;
        if (score >= 90) ++A;
        else if (score >= 80) ++B;
        else if (score >= 70) ++C;
        else if (score >= 60) ++D;
        else ++E;
    }
    printf("%d %d %d %d %d\n", A, B, C, D, E);
    return 0;
}
