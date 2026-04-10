#include <stdio.h>

int CountDigit( int number, int digit );
    
int main()
{
    int number, digit;

    scanf("%d %d", &number, &digit);
    printf("Number of digit %d in %d: %d\n", digit, number, CountDigit(number, digit));
    
    return 0;
}

/* 你的代码将被嵌在这里 */
int CountDigit( int number, int digit )
{
    int i,n=1,temp,k;
	if(number<0)
	number=-number;
	
	temp=number;
	int p[100];
	
	for(i=0;temp!=0;i++)
	{
		p[i]=temp%10;
		temp/=10;
	}
	for(k=0;k<i;k++)
	{
		if(p[k]==digit)
		n++;
	}
	return n;
}
