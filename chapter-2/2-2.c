#include <stdio.h>
#include <limits.h>
#include <float.h>

void main(void) {
	// i < lim-1 && (c=getchar()) != '\n' && c != EOF
	const int lim = 1000 < INT_MAX ? 1000 : 10;

	int i=0;
	int okLoop = 1;
	int c;
	char s[lim];

	while (okLoop) {
		if (i>=lim-1)
			okLoop = 0;
		else if ((c=getchar()) == '\n')
			okLoop = 0;
		else if (c == EOF)
			okLoop = 0;
		else 
			i++;
			s[i] = c;
	}
}
