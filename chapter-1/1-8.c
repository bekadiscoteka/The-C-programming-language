#include <stdio.h>
// program for counting blanks, tabs and newlines
#define ZERO 0

void main() {
    // counter
    long nc = ZERO;
    int c; 
    while ((c = getchar()) != EOF) 
        if (c == '\n' || c == '\t' || c == ' ') 
            ++nc;
    printf("count value: %ld\n", nc);
}
