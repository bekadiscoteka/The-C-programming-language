#include <stdio.h>

// histogram of lengths

#define IN 1
#define OUT 0
#define MID 5

main() {
    // initialize and fill up
    int arr[11];
    int nw, nc, c, state;
    nw = nc = c = 0;
    printf("Word length Histogram\n");
    for (int i = 1; i<11; ++i) 
        arr[i] = 0;
    
    while ((c=getchar()) != EOF) {
        if ( c=='\n' || c == '\t' || c==' ' ) {
            state = OUT;
            ++arr[nc];
            nc = 0;
            ++nw;
        }
        else {
            if ( state == OUT ) {
                state = IN;
            }
            ++nc; 
        }
        
    }
    
    if (nc != 0) {
        ++arr[nc];
        ++nw;
        nc=0; // optional
    }

    for (int i=0; i<11; ++i) {
        if (i == MID) printf("Word length's");
        else printf("\t"); 
    }
    putchar('\n');
    for (int i=1; i<11; ++i) printf("\t%2d", i);
    putchar('\n');
    for (int i=1; i<11; ++i) printf("\t%2d", arr[i]);
    putchar('\n');

    printf("Overall number of words: %d\n", nw);

}
