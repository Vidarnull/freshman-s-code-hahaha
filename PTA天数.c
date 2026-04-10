#include <stdio.h>

int main() {
    int year, month, day;
    scanf("%d/%d/%d", &year, &month, &day);

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    int totalDays = 0;
    switch (month - 1) {
        case 11:
            totalDays += daysInMonth[11];
        case 10:
            totalDays += daysInMonth[10];
        case 9:
            totalDays += daysInMonth[9];
        case 8:
            totalDays += daysInMonth[8];
        case 7:
            totalDays += daysInMonth[7];
        case 6:
            totalDays += daysInMonth[6];
        case 5:
            totalDays += daysInMonth[5];
        case 4:
            totalDays += daysInMonth[4];
        case 3:
            totalDays += daysInMonth[3];
        case 2:
            totalDays += daysInMonth[2];
        case 1:
            totalDays += daysInMonth[1];
        default:
            break;
    }
    totalDays += day;

    printf("%d\n", totalDays);

    return 0;
}