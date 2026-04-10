#include<stdio.h>
int main()
{
	int n,sc,i,k;
	scanf("%d",&n);
	int a[5]={0,0,0,0,0,};
	for(i=1;i<=n;i++)
	{
	  	scanf("%d",&sc);
	  	switch(sc/10){
	  		case 0:
	  		case 1:
	  		case 2:
	  		case 3:
	  		case 4:
	  		case 5: a[0]++;
	  		        break;
	  		case 6: a[1]++;
	  		        break;
	  		case 7: a[2]++;
	  		        break; 
	  		case 8: a[3]++;
	  		        break;
	  		case 9:        
			case 10: a[4]++;
	  		        break;
	  			 
		  }
	   }
    	printf("%d %d %d %d %d",a[4],a[3],a[2],a[1],a[0]);	
    	return 0;
	}	

