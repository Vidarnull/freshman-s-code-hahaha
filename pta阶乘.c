#include<stdio.h>
int main(){
    int n,fact,sum;
    fact=1;
    sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        fact=fact*i;
        sum=sum+fact;
    }
    printf("%d",sum);
    return 0;
}
#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) {
        printf("0\n");
        return 0;
    }

    int sum = 0;
    int fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
        sum += fact;
    }
    printf("%d\n", sum);
    return 0;
}