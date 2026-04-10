#include <stdio.h>

int main() {
    int A;
    scanf("%d", &A);

    if (A < 0) {
        printf("Invalid Value!");
    } else if (A <= 50) {  // 0 ≤ A ≤ 50
        float B = A * 0.53;
        printf("cost = %.2f\n", B);
    } else {  // A > 50
        float B = 50 * 0.53 + (A - 50) * 0.58;
        printf("cost = %.2f\n", B);
    }

    return 0;
}