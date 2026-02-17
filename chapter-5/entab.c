#include <stdio.h>
#include "mystd.h"
#include "mystring.h"
#include "ctype.h"
#define DEFAULT_TABSTOP 8
#define LINESIZE 100

char *entab(char str[], int tabstop) {
	int blankc = 0, i;
	char temps[1000];
	char *tempsp;

	for (i=0, tempsp = temps; str[i] != '\0'; ++i) {
		if (isspace(str[i])) 
			if (i+1 % tabstop == 0) {
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

char *detab(char s[], int tabstop) {
	char temps[1000];
	char *tempsp = temps;
	for (char *sp = s; *sp != '\0'; ++sp) {
		if (*sp == '\t') {
			for (int i=0; i < tabstop; ++i) 
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
	int tabstop;
	if (argc > 2 && (tabstop = catoi(*++argv)) > 0) 
		;
	else 
		tabstop = DEFAULT_TABSTOP;


	size_t size;
	char line[LINESIZE];
	while ((size = cgetline(line, LINESIZE)) > 0) {
		entab(line, tabstop);
		detab(line, tabstop);
		printf("\n%s\n", line);
	}

}
