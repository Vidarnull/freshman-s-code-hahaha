#include<stdio.h>
int main()
{
	int n,i;
	double p[50],ave=0,max,min;
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		scanf("%f",&p[i]);
	}
	
	for(max=p[0],i=1;i<n;i++)
	{
		if(p[i]>max)
		  max=p[i];
	}
	
	for(min=p[0],i=1;i<n;i++)
	{
		if(p[i]<min)
		  min=p[i];
	}
	
	for(i=0;i<n;i++)
	{
		ave=ave+p[i];
	}
	ave=ave/n;
	printf("average = %.2f\nmax = %.2f\nmin = %.2f",ave,max,min);
	return 0;
} 
