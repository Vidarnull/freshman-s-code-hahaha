#include <stdio.h>

int main() {
    int year, month, day;
    
    // 按照"mm-dd-yyyy"格式读取输入
    scanf("%d-%d-%d", &month, &day, &year);
    
    // 按照"yyyy-mm-dd"格式输出，使用%02d确保两位显示
    printf("%04d-%02d-%02d\n", year, month, day);
    
    return 0;
}