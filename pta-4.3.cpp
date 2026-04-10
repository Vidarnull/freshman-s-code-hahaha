#include<stdio.h>
int main()
{
	int day,a;
	scanf("%d",&day);
	a=day%5;
	if(a>=1&&a<=3)
	printf("Fishing in day %d",day);
	else
	printf("Drying in day %d",day);
	return 0;

 } 
