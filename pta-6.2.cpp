#include <stdio.h>

int sign( int x );

int main()
{
    int x;

    scanf("%d", &x);
    printf("sign(%d) = %d\n", x, sign(x));
    
    return 0;
}

/* 你的代码将被嵌在这里 */
int sign(int x)
{
	int r;
	if(x>0)
	r=1;
	else if(x=0)
	r=0;
	else
	r=-1;
	return r; 
}
