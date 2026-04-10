#include <stdio.h>

void matrix(int length, int width, char ch);

int main()
{    
    int length, width;
    char ch;

    scanf("%d %d %c", &length, &width, &ch);
    matrix(length, width, ch);

    return 0;
}

void matrix(int length, int width, char ch) 
{
	int k,i;
	for(i=0;i<width;i++)
	{
		for(k=0;k<length;k++)
		{
			printf("%c",ch);
		}
		printf("\n");
	}
}
