#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"
static char buf[MAXSIZE];
static int bufp=0;

static int singlebuf=0;

void ungetch(int c) {
	if (c == EOF) printf("\nEOF file detected\n");
	singlebuf == 0 ? singlebuf=c : printf("\nSingle buffer overflow\n");	
}


void ungets(char s[]) {
	int i;	
	for (i=0; s[i] != '\0'; ++i) 
		;
	if (i > 0) {
		i--;
		for (; i>=0; --i)
			ungetch(s[i]);
			bufp < MAXSIZE ? buf[bufp++] = s[i] : printf("\nbuffer overflow\n");
	}
}



int getch(void) {
	if (singlebuf != 0) {
		printf("\nsinglebuf = %d", singlebuf);
		int temp = singlebuf;
		singlebuf = 0;
		return temp;
	}
	return getchar();
}

int line[MAXSIZE];
int li=0;

int getdigit(char arr[], int i) { // i is a startpoint
	int c;								  //
	blank_skip();
	while (isdigit(c=line[li++]))
		arr[i++] = c;

	for (; isdigit(line[li]); ++li)
		arr[i++] = line[li];

	if (line[li] == '.') {
		arr[i++] = '.';

		for (++li; isdigit(line[li]); ++li)
			arr[i++] = line[li];
	}

	arr[i] = '\0';	
	return i;  // returns index of end of string
}

void blank_skip(void) {
	for (; line[li] == ' ' || line[li] == '\t' || line[li] == '\n'; ++li)
		;
}

int getop(char arr[]) {
	int n=0, i=0, c;
	blank_skip();
	if (line[li] == '\0') {
		c_getline(line, MAXSIZE);
		li = 0;
		return SKIP;
	}
	else if (isdigit(line[li])) {
		digit:
			getdigit(arr, i);
			return NUMBER;
	}

	else if (line[li] == EOF) {
		return EOF;
	}

	else if (line[li] == '-') {
		if (isdigit(line[li+1])) {
			li++;
			arr[i++] = '-';
			goto digit;
		}
	}

	if (isalpha(line[li])) {
		if (isupper(line[li])) {
			for (; isalpha(line[li]) && isupper(line[li]); ++li)
				arr[i++] = line[li];
			arr[i] = '\0';
			return CMD;
		}
		else {
			char var=line[li];
			for (++li; line[li] == ' ' || line[li] == '\t'; ++li)
				;

			if (line[li] == '=') {
				for (++li; line[li] == ' ' || line[li] == '\t'; ++li)
					;

				if (isdigit(line[li])) {
					arr[i++] = var;
					getdigit(arr, i);					
					return VAR_DEF;	
				}
				return UNKNOWN;
			}	
			else {
				arr[0] = var;
				arr[1] = '\0';
				return VAR;	
			}
		}
	}

	

	c = arr[i++] = line[li++];
	arr[i] = '\0';
	return c;
}


