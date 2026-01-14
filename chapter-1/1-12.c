#include <stdio.h>

#define IN 1
#define OUT 0
#define NL '\n'
#define TAB '\t'
#define BLANK ' '

main() {
    int nl, nc, nw, c, state;

    nl = nc = nw = state = OUT;

    printf("Welcome to word counter program, type your sentence until EOF(-1)\n");

    while ((c = getchar()) != EOF) {
        if (c == NL)                            ++nl;
        if (c == TAB || c == BLANK || c == NL){ state = OUT; putchar('\n'); }
        else if (state == OUT)                { state = IN; ++nw; putchar(c);} 
        else putchar(c);
        ++nc;
    }

    printf("Number of char-s: %d\nNumber of words %d\n", nc, nw);
}
