#include <stdio.h>

void main() {
    int c;
    printf("first input, put just single character and press enter\n");

    printf("condition: %d\n", c = getchar() == EOF); // checking priority, if EOF c is 1 otherwise 0
    
    printf("EOF value is %d\n", EOF);
    while ((c = getchar()) != -1) putchar(c); // EOF is -1
    printf("end of the program");
    
}
