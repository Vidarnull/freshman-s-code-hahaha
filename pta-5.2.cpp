#include <stdio.h>
int main()
{
	int a,n,i,k;
	int p[11];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	for(k=0;k<n-1;k++)
		{
			a=p[k+1]-p[k];
			printf("%d",a);
			if(k!=n-1)
			{
			if(k%3!=2)
			printf(" ");
			else
			printf("\n");}
		 } 
    return 0;
 } 
