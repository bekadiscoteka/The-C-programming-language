#include <stdio.h>
#include "mystd.h"
#include "mystring.h"
#include <ctype.h>
#define DEFAULT_OFFSET 0
#define DEFAULT_TABSTOP 8
#define LINESIZE 100

char *entab(char str[], int tabstop, int offset) {
	int blankc = 0, i=0;
	char temps[1000];
	char *tempsp = temps;

	while (i < offset) {
		if (isspace(str[i])) {
			blankc++;
			i++;
		}	
		else {
			while (blankc > 0) 
				*tempsp++ = ' ';
			*tempsp++ = str[i++];		
		}
	}
	
	if (blankc > 0) {
		*tempsp++ = '\t';
		blankc = 0;
	}
	for (; str[i] != '\0'; ++i) {
		if (isspace(str[i])) 
			if ( (i+1 - offset) % tabstop == 0 ) {
				blankc = 0;
				*tempsp++ = '\t';
			}
			else 
				blankc++;

		else {
			while (blankc > 0) { 
				*tempsp++ = ' ';
				blankc--;
			}
			*tempsp++ = str[i];
		}

	}
	*tempsp = '\0';

	c_strcpy(str, temps);	
	return str;
}

char *detab(char s[], int tabstop, int offset) {
	char temps[1000];
	char *tempsp = temps;
	char *next_tabstop = temps + offset;
	for (char *sp = s; *sp != '\0'; ++sp) {
		if (tempsp == next_tabstop)
			next_tabstop += tabstop;
		if (*sp == '\t') {
			while (tempsp < next_tabstop)
				*tempsp++ = ' ';			
			continue;
		}
		*tempsp++ = *sp;
	}
	*tempsp = '\0';

	c_strcpy(s, temps);
	return s;
}

int main(int argc, char *argv[]) {
	int tabstop = DEFAULT_TABSTOP;
	int offset = DEFAULT_OFFSET;

	while (--argc > 0) {
		switch (**++argv) {
			case '-':
				tabstop = catoi(*argv + 1);
				break;
			case '+':
				offset = catoi(*argv + 1);
				break;
			default:
				printf("\nundefined command-argument: %s", *argv);
		}
	}

	printf("\ntabstop %d\noffset %d\nenter empty line to quit\n", tabstop, offset);
	
	size_t size;
	char line[LINESIZE];
	while ((size = cgetline(line, LINESIZE)) > 0) {
		entab(line, tabstop, offset);
		detab(line, tabstop, offset);
		printf("\n%s\n", line);
	}

}
