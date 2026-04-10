#include<stdio.h>
int main()
{
    int n,num,a1,a2,a3,a4,a5,a6,k,i;
    scanf("%d",&n);
    int y[100];
    for(i=1;i<=n;i++)
       {
       	scanf("%d",&num);
       	a1=num/100000;
       	a2=num/10000-10*a1;
       	a3=num/1000-100*a1-10*a2;
       	a4=num/100-1000*a1-100*a2-10*a3;
       	a5=num/10-10000*a1-1000*a2-100*a3-10*a4;
       	a6=num-100000*a1-10000*a2-1000*a3-100*a4-10*a5;
       	if((a1+a2+a3)==(a4+a5+a6))
             	y[i]=1;
		else
				y[i]=0;
	      }
	for(k=1;k<=n;k++)
	   {
	   	if(y[k]==1)
	   	   printf("You are lucky!\n");
	   	else
	   	   printf("Wish you good luck.\n"); 
		   }     

	return 0;	
 } 
