#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 1000

int htoi(char hex[]);


void main() {
	char c;
	char hex[MAXSIZE];
	int i=0;
	while ((c=getchar()) != EOF && i < MAXSIZE) 
		if (c=='\n') {
			hex[i] = '\0';
			i=0;
			printf("\n%d\n", htoi(hex));
		}
		else 
			hex[i++] = c;

	printf("\nProgram stopped\n");
}

int htoi(char hex[]) {
	int n=0, i=0;

	if (hex[0] == '0')
		i = 2;

	for (; hex[i] != '\0'; i++) {
		if (isdigit( (char) hex[i])) 
			n = 16*n + (hex[i] - '0');
		else if ('a' <= hex[i] && hex[i] <= 'f')
			n = 16*n + (hex[i] - 'a') + 10;
		else if ('A' <= hex[i] && hex[i] <= 'F') 
			n = 16*n + (hex[i] - 'A') + 10;
	}

	return n;
}
