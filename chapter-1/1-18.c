#include <stdio.h>
#define MAXSIZE 100
int getlinef(char arr[], int size); 

void main() {
	char line[MAXSIZE];
	int c;

	while ((c=getlinef(line, MAXSIZE)) > 0) 
		if (line[0] != '\n') printf("%s", line);

	if (line[0] != '\n') printf("%s", line);
}


int getlinef(char arr[], int size) {
	int c, prev;
	int i;
	
	i=0;
	prev=0;

	while ((c=getchar()) != '\n') {
		if (c == EOF) {
			arr[i] = '\n';
			arr[++i] = '\0';
			return 0;
		}
		if (!((c == ' ' || c == '\t') && (prev == ' ' || prev == '\t'))) {
			arr[i++] = c;
			prev = c;
		}
	}

	arr[i] = '\n';
	arr[++i] = '\0';
	return i;
}
