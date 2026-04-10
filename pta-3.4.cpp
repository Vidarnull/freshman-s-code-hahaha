#include <stdio.h>
int main() {
    int cm;
    scanf("%d", &cm);
    double inches = cm / 2.54;
    
 
    int inche = (int)inches;
    
    int feet = inche/ 12;
    int inch = inche%12;
    printf("%d %d\n", feet, inch);
    
    return 0;
}
