#include<stdio.h>
int main()
{
    int a,b,r1,r2,r3,r4,r5;
	scanf("%d %d",&a,&b);
	r1=a+b;
	r2=a-b;
	r3=a*b;
	r4=a/b;
	r5=a%b; 
	printf("%d + %d = %d\n%d - %d = %d\n%d * %d = %d\n%d / %d = %d\n%d %% %d = %d",a,b,r1,a,b,r2,a,b,r3,a,b,r4,a,b,r5);
	return 0;
} 
