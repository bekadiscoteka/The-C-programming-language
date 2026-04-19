#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// time saver: inlines code
#define ISUPPER_time(c) ((c > 64) && (c < 91))
#define FRAND() ((double) rand() / ((double) RAND_MAX))
// space saver
int isupper_space(int c) {
	if (c > 64 && c < 91) 
		return 1;
	return 0;
}


int main(int argc, char* argv[]) {
	int maxiter;
	if ( argc < 2 || (sscanf(*(++argv), "%d", &maxiter) == 0) ) {
		fprintf(stderr, "Expected number argument: how many cycles do you want?");
		return 1;
	}

	printf("%d", maxiter);

	for (int i = 0; i < maxiter; ++i) {
		int randchar = CHAR_MAX * FRAND();	
		printf("%d randchar: %c\nSpace=%d, time=%d\n", i, randchar, isupper_space(randchar), ISUPPER_time(randchar));
	}
	return 0;
	
}
