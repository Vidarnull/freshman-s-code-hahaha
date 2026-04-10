#include<stdio.h>
int main()
{
	int a;
	scanf("%d",&a);
	if(a<0) 
	printf("Invalid Value!");
    else if(a>=0&&a<=50)
	printf("cost = %.2f",0.53*a);
	else
	printf("cost = %.2f",50*0.53+(a-50)*0.58);
	return 0;

 } 
