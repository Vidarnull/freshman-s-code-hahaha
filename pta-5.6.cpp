#include <stdio.h>

int main()
{
    int i,mub;
    char a[100];
    gets(a);
    if(a[0]!=' ')
    mub=1;
    else
    mub=0;
    for(i=1;a[i]!='\0';i++)
    {
    	if(a[i]!=' '&&a[i-1]==' ')
    	mub++;
	}
    return 0;
}
