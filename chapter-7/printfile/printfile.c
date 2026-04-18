#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define MAXLINE 6


int main(int argc, char* argv[]) {
	void* argv_init = ++argv;
	const char HEADER_TEMPL[] = {
		"\f=================\n"
		"%s: page %d\n"
		"==================\n"
		};
	
	if (argc < 2) {
		fprintf(stderr, "No files to output\n");
		return 1;
	}

	while (*argv != NULL) {
		FILE *fd;
		if ((fd=fopen(*argv, "r")) != NULL) {

			unsigned page = 1;
			char line[MAXSIZE];
			unsigned linec = 0;

			printf(HEADER_TEMPL, *argv, page);	
			while (fgets(line, MAXSIZE, fd) != NULL) {
				if (linec >= page * MAXLINE) {
					printf(HEADER_TEMPL, *argv, ++page);
				}
				printf("%d %s", linec++, line);
			}

			printf("- Enter q - for quitting, n - for next file%s", argv != argv_init ? ", p - for previous\n" : ".\n" );	

			int invalid = 1;

			while (invalid) {
				int user_resp = getchar();
				switch (user_resp) {
					case 'q': case EOF:
						printf("quitting the program\n");
						return 0;
					case 'p':
						if (argv == argv_init) 
							;
						else {
							--argv;
							invalid = 0;
							printf("\033[A\033[2K\r\033[A\033[2K\r");
						}
						break;
					case 'n':
						++argv;
						invalid = 0;
						printf("\033[A\033[2K\r\033[A\033[2K\r");
						break;
				}
			}

		}

	}
	printf("End of program\n");
	return 0;
}
