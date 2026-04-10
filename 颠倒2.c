#include <stdio.h>

int main() {
    char str[1000];      // 存储输入的字符串
    char result[1000];   // 存储最终结果
    int len = 0;         // 输入字符串的实际长度
    int i, j, k;
    
    // 1. 读取一整行输入（可以包含空格）
    printf("请输入: ");
    for (i = 0; i < 1000; i++) {
        str[i] = getchar();
        if (str[i] == '\n') {
            break;
        }
        len++;
    }
    str[len] = '\0';  // 字符串结束标记
    
    // 2. 核心处理：从后往前找单词，并保留原始空格
    k = 0;  // result数组的下标
    
    for (i = len - 1; i >= 0; ) {
        // 跳过末尾的空格
        while (i >= 0 && str[i] == ' ') {
            i--;
        }
        
        // 记录当前单词的结束位置
        int word_end = i;
        
        // 找到当前单词的开始位置
        while (i >= 0 && str[i] != ' ') {
            i--;
        }
        // 此时i指向单词前面的空格或-1
        
        // 3. 把这个单词复制到result中
        for (j = i + 1; j <= word_end; j++) {
            result[k] = str[j];
            k++;
        }
        
        // 4. 复制单词前的所有空格到结果中
        int space_count = 0;
        while (i >= 0 && str[i] == ' ') {
            space_count++;
            i--;
        }
        
        // 将空格添加到结果中（保持原始空格数量）
        for (j = 0; j < space_count; j++) {
            result[k] = ' ';
            k++;
        }
    }
    result[k] = '\0';  // 结果字符串结束
    
    // 5. 输出
    printf("颠倒后: %s\n", result);
    
    return 0;
}