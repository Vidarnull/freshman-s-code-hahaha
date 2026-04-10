#include<stdio.h>
void clear_screen() 
{
    for(int i = 0; i < 50; i++) {
        printf("\n");
    }
}

int main() {
    printf("内容将被清空...\n");
    getchar();
    
    clear_screen();
    printf("新的开始！\n");
    return 0;
}
