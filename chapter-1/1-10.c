#include <stdio.h>
// program for counting blanks, tabs and newlines
#define ZERO 0

void main() {
    int c;
    int prev = EOF;
    while ((c = getchar()) != EOF) {
        if (!(c == ' ' && c == prev)) putchar(c);
        prev = c;
    } 

}
