#include<stdio.h>
int main()
{
	printf("随便输一个数字好不好，正负都可以的XwX\n"); 
	int munber1,munber,i=0,n=1;
	int a[100];
	scanf("%d",&munber1);
	if(munber1<0)
	   {
	   munber=-munber1;
       }  
	else 
	   munber=munber1;
	while(munber>=10)
	{
		a[i]=munber%10;
		munber=munber/10;
		i++;
		n++;
	   }   
	a[i]=munber;
	
	if(munber1<0)
	  printf("fu ");
	else
	  ;
	
	for(i=n-1;i>=0;i--)
	{
	switch(a[i]){
	  case 0:printf("ling");break;
	  case 1:printf("yi");break;
	  case 2:printf("er");break;
	  case 3:printf("san");break;
	  case 4:printf("si");break;
	  case 5:printf("wu");break;
	  case 6:printf("liu");break;
	  case 7:printf("qi");break;
	  case 8:printf("ba");break;
	  case 9:printf("jiu");break;
      }
	if(i>0)
	printf(" ");
    }
 return 0; 
}
