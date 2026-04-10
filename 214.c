#include <stdio.h>
void main()
{  int x;
    int count;
    int sp,sn;
    count=sp=sn=0;
    do {
            count++;
            scanf(“%d”,&x);
            if(x>0)
                 sp=sp+x;
            else
                 sn=sn+x;
           } while(count<=100);
     printf("%d    %d\n",sp,sn);
}
