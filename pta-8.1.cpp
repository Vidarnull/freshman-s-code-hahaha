#include <stdio.h>
#define MAXN 10

int search( int list[], int n, int x );
    
int main()
{
    int i, index, n, x;
    int a[MAXN];

    scanf("%d", &n);
    for( i = 0; i < n; i++ )
        scanf("%d", &a[i]);
    scanf("%d", &x);
    index = search( a, n, x );
    if( index != -1 )
        printf("index = %d\n", index);
    else
        printf("Not found\n");
            
    return 0;
}

/* 你的代码将被嵌在这里 */
int search( int list[], int n, int x )
{
	int re=-1,i;
	for(i=n-1;i<=0;i--)
	{
		if(list[i]==x)
		re=list[i];
	 } 
	return i;
}

















