#include <stdio.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    while (N--) {
        int x;
        if (scanf("%d", &x) != 1) break;
        int d1 = (x / 100000) % 10;
        int d2 = (x / 10000) % 10;
        int d3 = (x / 1000) % 10;
        int d4 = (x / 100) % 10;
        int d5 = (x / 10) % 10;
        int d6 = x % 10;
        int sum1 = d1 + d2 + d3;
        int sum2 = d4 + d5 + d6;
        if (sum1 == sum2) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}