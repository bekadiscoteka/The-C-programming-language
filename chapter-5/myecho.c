#include <stdio.h>
int main(int argc, char *argv[]) {
	while (--argc > 0) {
		for (char *c = *++argv; *c != '\0'; ++c) 
			putchar(*c);
		putchar(' ');
	}
	return 0;
}
