#include<stdio.h>
#include<math.h> 
int main()
{
	double  money,year,rate,interest,a;
	scanf("%lf %lf %lf",&money,&year,&rate);
	a=pow(1+rate,year);
	interest=a*money-money;
	printf("interest = %.2lf",interest);
}
