#include <stdio.h>
int main()
{
	int a,n,i,k,b=0;
	int p[11];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&p[i]);
	}
	a=p[0];
	b=0;
	for(k=1;k<n;k++)
	{
		if(a<p[k])
		  {
		  a=p[k];
		  b=k;}	  		  
	}
	printf("%d %d",a,b);
 } 
