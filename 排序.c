#include <stdio.h>

// 选择排序函数
void sort(int *a, int n) {
    int i, j, k, t;
    for (i = 0; i < n - 1; i++) {
        k = i;                     // 假设当前元素为最小
        for (j = i + 1; j < n; j++) {
            if (*(a + j) < *(a + k)) {
                k = j;             // 记录更小元素的位置
            }
        }
        // 将最小元素交换到当前位置
        t = *(a + i);
        *(a + i) = *(a + k);
        *(a + k) = t;
    }
}

int main() {  // 建议使用标准int main()而不是void main()
    int b[10] = {5, 10, 6, 9, 8, 2, 7, 4, 3, 1};
    int i;
    
    sort(b, 10);  // 调用排序函数对数组b进行排序
    
    // 输出排序后的数组
    for (i = 0; i < 10; i++) {
        printf("%4d ", b[i]);
    }
    printf("\n");
    
    return 0;  // 返回0表示程序正常结束
}