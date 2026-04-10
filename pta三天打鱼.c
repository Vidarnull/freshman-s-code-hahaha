#include <stdio.h>
int main() {
    int A;
    scanf("%d", &A);
    int B = A % 5;
    if (0 < B && B < 4) {
        printf("fishing in day %d\n", A);
    } else {
        printf("drying in day %d\n", A);
    }
}