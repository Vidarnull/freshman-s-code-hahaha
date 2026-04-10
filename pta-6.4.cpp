#include <stdio.h>

int narcissistic( int number );
void PrintN( int m, int n );
    
int main()
{
    int m, n;
  
    scanf("%d %d", &m, &n);
    if ( narcissistic(m) ) printf("%d is a narcissistic number\n", m);
    PrintN(m, n);
    if ( narcissistic(n) ) printf("%d is a narcissistic number\n", n);

    return 0;
}

/* 你的代码将被嵌在这里 */
int narcissistic( int number )
{
	int i,r=0,r1,k,n,r2;
	int p[100];
	r2=number;
	for(i=0;number!=0;i++)
	{
	    p[i]=number%10;
		number=number/10;	
	}
	for(k=0;k<i;k++)
	{
		for(n=0,r1=p[k];n<i-1;n++)
		{
			r1=r1*p[k];
		}
		r=r+r1;
	}
	if(r==r2)
	   return 1;
    else
       return 0;
}
void PrintN( int m, int n )
{
	int i;
	for(i=m+1;i<n;i++)
	{
		if(narcissistic(i)==1)
		  printf("%d\n",i);
	 } 
}
