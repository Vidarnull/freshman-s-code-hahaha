#include <stdio.h>
#include <conio.h>  // Windows-specific header file

int main() {
    printf("Press any key to continue... (Press q to quit)\n");
    
    while(1) {
        // Read character in real-time, no need for Enter key
        char ch = getch();
        
        printf("You pressed: %c\n", ch);
        
        if(ch == 'q' || ch == 'Q') {
            break;
        }
    }
    
    return 0;
}