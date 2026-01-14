#include <stdio.h>
#define MAXSIZE 10 
#define LIM 10
#define INPUT_LIM 15

int lgetline(char arr[], int size);
int lappend(char dest[], char src[], int start);

void main() {
	char line[MAXSIZE], above_lim[INPUT_LIM]; // consider \0
	int len=0, start=0;

	while ((len = lgetline(line, MAXSIZE)) > 0) {
		if (len > LIM && start+len < INPUT_LIM-1)
			start = lappend(above_lim, line, start);
	}

	above_lim[start] = '\0';

	printf("final result: %s", above_lim);	
}

int lgetline(char arr[], int size) {

	int i=0;	
	int c;

	while ((c=getchar()) != '\n') {
		if (c == EOF) return 0;	
		if (i<size-1) arr[i] = c;
		++i;
	}
	if (i < size-1) 
		arr[i] = '\n';
	else 
		arr[size-1] = '\n';
	return i;
}

int lappend(char dest[], char src[], int start) {
	int i;
	
	for (i=0; src[i] != '\n'; ++i) 
		dest[start+i] = src[i];

	dest[start+i] = '\n';
	src[i++] = ' ';	
	return start+i;
}





