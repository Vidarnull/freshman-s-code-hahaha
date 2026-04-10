#include<stdio.h>
int main()
{
	int a,b,n;
	double a1,b1,m;
	scanf("%d %d",&a,&b);
	n=a/b;a1=a;b1=b;m=a1/b1;
	printf("%d + %d = %d\n",a,b,a+b);
	printf("%d - %d = %d\n",a,b,a-b);
	printf("%d * %d = %d\n",a,b,a*b);
	if(n==m)
	  printf("%d / %d = %d\n",a,b,a/b);
	else
	  printf("%d / %d = %.2f\n",a,b,a1/b1);   
 }  
