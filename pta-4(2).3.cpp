#include<stdio.h>
int main()
{
    int a,n,i,k,ji=0,ou=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
       {
       	scanf("%d",&a);
       k=a%2;
       if(k==1)
         ji++;
       else
         ou++;
	   }
	printf("%d %d",ji,ou);
	return 0;	
 } 
