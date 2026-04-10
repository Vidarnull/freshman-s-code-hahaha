#include<stdio.h>
int main()
{
	int score;
	char a;
	scanf("%d",&score);
	if(score>=90)
	  a='A';
    else if(score<90&&score>=80)
	  a='B';
    else if(score<80&&score>=70)
	  a='C';
	else if(score<70&&score>=60)
	  a='D';
	else
	  a='E';
	printf("%c",a);
	return 0;
} 
