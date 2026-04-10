#include <stdio.h>

int main() {
    int original_price, discount;
    
    // 读取商品原价和折扣
    scanf("%d %d", &original_price, &discount);
    
    // 计算折扣价：原价 × 折扣/10
    double discounted_price = original_price * (discount / 10.0);
    
    // 输出折扣价，保留两位小数
    printf("%.2f\n", discounted_price);
    
    return 0;
}