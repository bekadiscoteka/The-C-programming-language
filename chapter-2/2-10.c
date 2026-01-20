#include <stdio.h>

char lower(char c);

int main(void) {
	char c = lower('A');
	putchar(c);
}

char lower(char c) {
	return (c >= 'A' && c <= 'Z') ? ('a' - ('A' - c)) : c;
}
