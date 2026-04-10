#include <stdio.h>
int main()
{
    int score1, score2, score3, m, n, k;
    scanf("%d%d%d", &score1, &score2, &score3);
    m=score1>score2?score1:score2;	// m取score1、score2中较大数
    m=m>score3?m:score3;		// m取m、score3中较大数
    n=score1<score2?score1:score2;	// n取score1、score2中较小数
    n=n<score3?n:score3;		// n取n、score3中较小数
    k=score1+score2+score3-m-n; //3个数的和减去最大、最小数，得中间数
    printf("%d  %d  %d\n", m, k, n);
    return 0;
}
// 该程序输入3个整数，输出其中的最大数、中间数和最小数。