#include <stdio.h>
int main() 
{
	int x,y,s1,s2,s3,s4,s5;
	scanf("%d %d",&x,&y);
	s1=100*100/2;
	s2=x*y/2;
	s3=(100-x)*y;
	s4=(100-x)*(100-y)/2;
	s5=s1-s2-s3-s4;
	printf("%d",s5);
	
}
