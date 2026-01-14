#include <stdio.h>
#define MAXSIZE 5 

int lgetline(char arr[], int size);
void lcopy(char source[], char dest[]);

void main() {
	char line[MAXSIZE], longest_line[MAXSIZE]; // consider \0
	int len=0, longest_len=0;

	while ((len = lgetline(line, MAXSIZE)) > 0) {
		if (len > longest_len) { 
			lcopy(line, longest_line);
			longest_len = len;
		}
	}

	if (longest_len > 0)
		printf("longest line\n\t %s \n\tsize:%d\n", longest_line, longest_len); 
}

int lgetline(char arr[], int size) {

	int i=0;	
	int c;

	while ((c=getchar()) != '\n') {
		if (c == EOF) return 0;	
		if (i<size-1) arr[i] = c;
		++i;
	}

	arr[i] = '\0';


	return i;

}

void lcopy(char from[], char to[]) {
	for (int i=0; from[i] != '\0'; i++) 
		to[i] = from[i];

}





