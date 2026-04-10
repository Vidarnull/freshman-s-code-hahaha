#include <stdio.h>
int main()
{
	char a[81];
	int n,k,i,m,p;
	gets(a);
	
	for(n=0;a[n]!='\0';n++)
	

	
		for(i=1,k=0,m=n;i<=n/2;i++,k++,m--)
		{
		     p=a[m];
		     a[m]=a[k];
			 a[k]=p;	 	
		}
	
	printf("%s",a);
}
