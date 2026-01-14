// doesn't consider the last line, without enter
#include <stdio.h>
#define MAXSIZE 100
#define TABSTOP 4

int get_blanknum(int currentPos, int tabstop);

void main(void) {
	int c, i;

	i=0;
	while ((c=getchar()) > EOF) {
		if (c == '\t') {
			for (int j=0; j < get_blanknum(i, TABSTOP); ++j) {
				putchar(' ');
				++i;
			}

		}
		if (c == '\n') { 
			i=0;
			putchar(c);
		}
		else {
			putchar(c);
			++i;
		}
	}
}

int get_blanknum(int pos, int tabstop) {
	return tabstop - (pos % tabstop);
}
