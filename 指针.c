#include<stdio.h>
void main()
{
    int a = 100, *pa;      // 定义整型变量a和整型指针pa
    pa = &a;               // 将a的地址赋给pa（使pa指向a）
    printf("a = %d, *pa = %d\n", a, *pa);  // 输出a的值和pa指向的值
    *pa = 200;             // 通过指针修改a的值为200
    printf("a = %d, *pa = %d\n", a, *pa);
    *pa += 1;              // 通过指针将a的值增加1
    printf("a = %d, *pa = %d\n", a, *pa);
}