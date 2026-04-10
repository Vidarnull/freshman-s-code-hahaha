#include <stdio.h>
int main()
{
	int a,n,sum=0,i,k,m;
	int p[11][11];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		for(k=0;k<n;k++)
		{
			scanf("%d",&p[i][k]);
			sum+=p[i][k];//所有加 
		}
	}
	for(i=n-1;i>=0;i--)
	{
		sum=sum-p[n-1][i];//最后行 
	}
	for(i=n-1;i>=0;i--)
	{
		sum=sum-p[i][n-1];//最后列 
	}
	for(i=n-1,m=0;i>=0;i--,m++)
	{
		sum=sum-p[m][i];
	}
	sum=sum+p[n-1][n-1]+p[1][n-1]+p[n-1][1];
	printf("%d",sum);
 } 
