#include <stdio.h>
int main()
{
	int a,n,m,k,i,b=0;
	scanf("%d %d",&m,&n);
	for(k=0;k<m;k++)
	{
	   for(i=0;i<n;i++)
	    {
		  scanf("%d",&a);
		  b=b+a;	
	    }
	    printf("%d\n",b);
	    b=0;
    }
    return 0;
 }  
