#include<stdio.h>
int main(){
	char a[80];
	int c[10]={0},i,n=0;
	scanf("%s",&a);
	for(i=0;a[i]!='\0';i++)
	{
		switch(a[i]){
			case '0': c[0]++;break;
			case '1': c[1]++;break;
			case '2': c[2]++;break;
			case '3': c[3]++;break;
			case '4': c[4]++;break;
			case '5': c[5]++;break;
			case '6': c[6]++;break;
			case '7': c[7]++;break;
			case '8': c[8]++;break;
			case '9': c[9]++;break;	
		}
    }
	for(i=0;i<10;i++)
	{
		if(c[i]>0)
		 {
		printf("%d:%d次 ",i,c[i]); 
		n++;}
		if(n%3==0)
		printf("\n");	   
	}
	if(n==0)
	printf("10个数字字符都没出现过");
	
    return 0;	
} 
