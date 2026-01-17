#include <stdio.h>
#define MAXSIZE 1000
#define LIM 20
#define BLANK 0
#define CHARAC 1
#define USED -1
int l_getline(char arr[], int size);
void l_fold(char dest[], char src[], int limit);

void main(void) {
	int size;
	char line[MAXSIZE], folded[MAXSIZE];

	while ((size=l_getline(line, MAXSIZE)) > 0) {
		if (line[0] != '\n') {
			printf("line: %s", line);
			l_fold(folded, line, LIM);
			printf("%s", folded);
		}
	}	
}

int l_getline(char arr[], int size) {
	int i, c;

	for (i=0; (c=getchar()) != '\n' && i < size-2; ++i) {
		if (c==EOF) return 0;
		arr[i] = c;	
	}

	arr[i++] = '\n';
	arr[i] = '\0';	
	return i;
}

void l_fold(char dest[], char src[], int lim) {
	int i=0, d=0, last_space=-1, column=0;

	while (src[i] != '\0') {
		if (src[i] == ' ') 
			last_space = d;

		if (column >= lim-1) {
			if (last_space != USED) {
				dest[last_space] = '\n';
				last_space = USED;
				column = d - last_space;
			}

			else {
				dest[d++] = '\n';		
				column = 0;
			} 
		}

		dest[d++] = src[i++];
		column++;
	}
	dest[d] = '\0';
}	
