#include<stdio.h>
int main()
{
	int i=1,k=1;
	double r=0.0,eps,m=100;
	scanf("%lf",&eps);
	for(i=1;m>eps;i=i+3,k=-k)
	    {
	    	m=1.0/i;
	    	if(k==1)
	    	  r=r+m;
			else
			  r=r-m; 
		}
	printf("sum = %.6lf",r);
	return 0;	
 } 
