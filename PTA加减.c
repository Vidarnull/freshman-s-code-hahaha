#include <stdio.h>
int main() {
    int A, B;
    scanf("%d %d", &A, &B);
    int C = A + B;
    int D = A - B;
    int E = A * B;
    printf("%d + %d = %d\n", A, B, C);
    printf("%d - %d = %d\n", A, B, D);
    printf("%d * %d = %d\n", A, B, E);
    if (A % B == 0)
    {
        printf("%d / %d = %d\n", A, B, A / B);
    }else{
        printf("%d / %d = %.2f\n", A, B, (float)A / (float)B);
    }

    return 0;

}