#include <stdio.h>

int main()
{
	int  m[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};
int year,month,leap;
scanf("%d%d",&year,&month);
leap=year%400==0 || year%100!=0 && year%4==0;
printf("%d\n",m[leap][month]);

return 0;
}