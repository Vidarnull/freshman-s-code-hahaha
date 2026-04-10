#include <stdio.h>
#include <string.h>

#define MAXN 20
typedef enum {false, true} bool;

bool palindrome( char *s );

int main()
{
    char s[MAXN];
    
    scanf("%s", s);
    if ( palindrome(s)==true )
        printf("Yes\n");
    else
        printf("No\n");
    printf("%s\n", s);

    return 0;
}

/* 你的代码将被嵌在这里 */ bool palindrome( char *s )
 {
 	int i,k,p=0;
 	for(i=0;*s[i]!='\0';i++){;
	}
	if(i==0)
	return true;
	else
	{
			for(k=0;k<i/2;k++)
			{
				if(*s[k]!=*s[i-k-1])
				p++;	
		    }
	}
	if(p==0)
	return true;
	else
	return false;
 }
