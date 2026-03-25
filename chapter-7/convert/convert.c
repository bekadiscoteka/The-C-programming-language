#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {

		char* temp;

		do {
			if (--argc == 0) {
				printf("Missing corresponding arguments: please provide arg u or l\n");
				return 0;
			}
		}
		while (strcmp((temp = *++argv), "u") != 0 && strcmp(temp, "l") != 0);


	    int c;
		if (temp[0] == 'u') {
			printf("UPPERCASE\n");
			while ((c=getchar()) != EOF) 
				putchar(toupper(c));
		}
		else {
			printf("LOWERCASE\n");
			while ((c=getchar()) != EOF)
				putchar(tolower(c));
		}

}
