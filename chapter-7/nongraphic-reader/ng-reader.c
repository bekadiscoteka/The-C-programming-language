#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 15

  /*
*//* 
*//* task: 7-2 
*//* solution
*//*
*/

int main(int argc, char *argv[]) {
	char outcfg[] = "\\0x%x";
	while (--argc > 0) {
		if (strcmp(*++argv, "-o") == 0) {
			strcpy(outcfg, "\\0%o");
			break;
		}
	}

	char c;
	int charcnt=0;

	while ((c=getchar()) != EOF) {
		if (charcnt++ == MAXLINE) {
			putchar('\n');
			charcnt = 0;
		}
		
		if (isprint(c)) 
			printf("%c", c);
		else 
			printf(outcfg, c);
	}

	return 0;
}


