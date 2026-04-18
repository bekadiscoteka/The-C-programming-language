#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int patsearch(FILE *fin, FILE *fout, const char *name, const char *pat) {

	if (fin == NULL) { 
		fprintf(stderr, "cannot open file: %s", name);
		return 0;
	}
	
	char line[MAXLINE];
	char *linep;
	unsigned linec=0, foundc=0;
	while ((linep=fgets(line, MAXLINE, fin)) != NULL) {
		while (*linep != '\0') {
			if (strncmp(pat, linep, strlen(pat)) == 0) {
				linep += strlen(pat);
				fprintf(fout, "%s line %d: %s", name, linec, line);
				foundc++;
			}
			else 
				linep++;
		}
		linec++;
	}
	return foundc;
}

int main(int argc, char *argv[]) {
	// feeder 
	FILE *fd; 
	char *fn;
	unsigned int found = 0;

	if (argc < 2) {
		fprintf(stderr, "No pattern to search\n");	
		return 1;
	}

	char* pat = *++argv;

	if (argc == 2) {
		fprintf(stderr, "No files entered, reading from stdin\n");
		fd = stdin;
		found += patsearch(stdin, stdout, "stdin", pat);
	}


	while (( fn = *++argv ) != NULL) 
		found += patsearch(fopen(fn, "r"), stdout, fn, pat);
	return 0;
}
