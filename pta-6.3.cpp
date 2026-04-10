#include <stdio.h>

int fib( int n );

int main()
{
    int n;

    scanf("%d", &n);
    printf("%d\n", fib(n));

    return 0;
}

/* 你的代码将被嵌在这里 */
int fib(int n)
{
	int a=1,b=1,c,r,k;
	if(n==1)
	r=1;
	else if(n==2)
	r=1;
	else
	{
	    for(k=0;k<n-2;k++)
	  {
	  	r=0;
		r=a+b;
		a=b;
		b=r;
		
	  }
    }
    return r;
}
