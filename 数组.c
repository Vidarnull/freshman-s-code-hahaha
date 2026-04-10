#include<stdio.h>
void main()
{
    int a[3][4], i, j, s = 0;  // 定义3行4列的二维数组a，以及循环变量i,j，累加和s
    int (*p)[4];               // 定义指向含有4个元素的一维数组的指针p
    p = a;                     // 将数组a的首地址赋给p，此时p指向二维数组的第0行
    
    printf("Please input data:\n");  // 提示输入
    
    // 双重循环：通过指针p输入数组的每个元素
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            scanf("%d", *(p + i) + j);  // 等价于 &a[i][j]
    
    // 双重循环：通过指针p累加所有数组元素的值
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            s += *(*(p + i) + j);  // 等价于 s += a[i][j]
    
    printf("s = %d\n", s);  // 输出总和
}