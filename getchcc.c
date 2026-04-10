#include<stdio.h>          // 包含标准输入输出库，提供getchar和putchar函数
void main()               // 主函数（建议使用int main()以符合现代标准）
{
    char c1, c2, c3;      // 定义三个字符变量
    c1 = getchar();       // 从键盘读取第一个字符，赋值给c1
    c2 = getchar();       // 读取第二个字符，赋值给c2
    c3 = getchar();       // 读取第三个字符，赋值给c3
    putchar(c1);          // 输出c1对应的字符
    putchar(c2);          // 输出c2对应的字符
    putchar(c3);          // 输出c3对应的字符
}