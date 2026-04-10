#include <stdio.h>
#define  Pi  3.14159
int main()
{   
    const int PI=3.14;
	double r,k,s;  
    scanf("%lf",&r);
    k=2*Pi*r;
    s=PI*r*r; 
    printf("circle£º%.2f    area£º%.2f\n",k,s); 
}
