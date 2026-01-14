// doesn't consider the last line, without enter
#include <stdio.h>
#define MAXSIZE 100
void lreverse(char dest[], char src[], int size);
int lgetline(char arr[], int size);

void main() {
	char line[MAXSIZE], reversed[MAXSIZE];
	int size;	

	while ((size=lgetline(line, MAXSIZE)) > 0) {
		if (line[0] != '\n') {
			lreverse(reversed, line, size);
			printf("%s\n", reversed);
		}
	}
}

int lgetline(char arr[], int size) {
	int c, i;

	for (i=0; i<size-1 && (c=getchar()) != '\n'; ++i) {
		if (c==EOF) {
			arr[i]='\0'; 
			return 0;
		}
		arr[i] = c;
	}
	arr[i] = '\0';
	return i;	
}

void lreverse(char dest[], char src[], int size) {
	for (int i=0; i<size; ++i)
		dest[size-1-i] = src[i];
}
