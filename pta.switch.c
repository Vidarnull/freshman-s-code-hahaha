#include <stdio.h>

int main() {
    int a;
    scanf("%d", &a);  // 输入一个百分制成绩

    switch (a / 10) {
        case 10:
        case 9:  // 90 ~ 100 → A
            printf("A\n");
            break;
        case 8:  // 80 ~ 89 → B
            printf("B\n");
            break;
        case 7:  // 70 ~ 79 → C
            printf("C\n");
            break;
        case 6:  // 60 ~ 69 → D
            printf("D\n");
            break;
        default: // 0 ~ 59 → E
            printf("E\n");
    }

    return 0;
}