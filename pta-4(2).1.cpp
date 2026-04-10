#include<stdio.h>
int main()
{
	int a=0,n,r=1,i,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		for(k=i;k>0;k--)
		{
			r=r*k;
		}
		a=a+r;
		r=1;
	}
    printf("%d",a);
	return 0; 
}
