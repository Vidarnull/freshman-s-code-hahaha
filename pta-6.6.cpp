 
#include<stdio.h>

#define M 10
#define N 4

void Input(float a[][N],int m);
float Sum(float a[][N],int m);
 

int main(void)
{
        float num[M][N],sum;
    
        int m;
        scanf("%d", &m);
        Input(num,m); 
    
        sum = Sum(num,m);
        printf("sum = %.2f\n", sum);
        return 0;
}

/* 请在这里填写答案 */
void Input(float a[][N],int m)
{
	int i,k;
	for(i=0;i<m;i++)
	{
		for(k=0;k<N;k++)
		   scanf("%d",&a[i][k]);
	}
}

float Sum(float a[][N],int m)
{
	float sum=0;
	int k,i;
	for(i=0;i<m;i++)
	{
		for(k=0;k<N;k++)
		{
			sum+=a[i][k];
		}
	}
	for(i=0;i<m;i++) 
	sum-=a[i][0];
	for(i=0;i<m;i++) 
	sum-=a[i][N-1];
	for(i=0;i<N;i++) 
	sum-=a[0][i];
	for(i=0;i<N;i++) 
	sum-=a[m-1][i];
	sum=sum+a[0][0]+a[0][N-1]+a[m-1][0]+a[m-1][N-1];
	return sum;
}
