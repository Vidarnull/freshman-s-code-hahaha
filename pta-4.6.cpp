#include<stdio.h>
int main()
{
    int year,month,day,n,m2; 
	scanf("%d/%d/%d",&year,&month,&day);
	if(year%4==0&&year%100!=0||year%400==0)
	  m2=29;
	else
	  m2=28;
    switch(month){
    	case 1:
    		n=0;break;
    	case 2:
    		n=31;break;
		case 3:
			n=31+m2;break;
		case 4:
			n=31+m2+31;break;
		case 5:	
		    n=31+m2+31+30;break;
		case 6:	
		    n=31+m2+31+30+31;break;
    	case 7:
    		n=31+m2+31+30+31+30;break;
		case 8:
			n=31+m2+31+30+31+30+31;break;
		case 9:
			n=31+m2+31+30+31+30+31+31;break;
		case 10:
			n=31+m2+31+30+31+30+31+31+30;break;
		case 11:
			n=31+m2+31+30+31+30+31+31+30+31;break;
		case 12:
			n=31+m2+31+30+31+30+31+31+30+31+30;break;
	    }
	printf("%d",day+n);
	return 0;
			
	}
