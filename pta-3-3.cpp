#include<stdio.h>
int main(void)
{
    int year,mouth,day;
    scanf("%d-%d-%d",&mouth,&day,&year);
    printf("%d-%.2d-%.2d",year,mouth,day);
	return 0;
} 
