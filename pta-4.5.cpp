#include<stdio.h>
int main()
{
	int a,b;
	char d;
	scanf("%d %c %d",&a,&d,&b);
	switch(d)
	{
		case '+':
			printf("%d",a+b);break;
		case '-':
			printf("%d",a-b);break;
		case '*':
			printf("%d",a*b);break;
		case '/':
			printf("%f",a/b);break;
		case '%':
			printf("%d",a%b);break;
		default:
		    printf("ERROR");break;		
	}
	return 0;
}
