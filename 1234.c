#include <stdio.h>
void main()
{   
	int x,y=7,a,b,c;
    	int z=4;
    	x=(y=y+6, y/z);
    	c*=(a=b=1, c=2, b+=a, b*5); 
    	printf("x=%d\n",x);
    	printf("a=%d,b=%d,c=%d",a,b,c);
}
/* This C code demonstrates the use of the comma operator in assignments.
   It calculates the value of 'x' based on the modified value of 'y' and
   performs a series of assignments to 'a', 'b', and 'c' using the comma operator.
   The results are printed to the console. */