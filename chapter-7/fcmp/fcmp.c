#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100
// fopen with error printing

FILE* fopen_err(char* name, char* mode) {
	FILE* ftemp = fopen(name, mode);

	if (ftemp == NULL) {
		fprintf(stderr, "Cannot open file %s, make sure file exists and you have appropriate permissions\n", name);
		exit(2);
	}
	/*
	if (ferror(ftemp))
		fprintf(stderr, "File %s doesn't exist\n");
		*/
	return ftemp;	
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "There should be 2 file names\n");
		exit(1);
	}
	
	FILE *file_a = fopen_err(argv[1], "r");
	FILE *file_b = fopen_err(argv[2], "r");

	char line_a[MAXLINE], line_b[MAXLINE];
	char *strtempa, *strtempb;
	int line = -1;

	do {
		line++;
		strtempa = fgets(line_a, MAXLINE, file_a); 
		strtempb = fgets(line_b, MAXLINE, file_b);
		if (strtempb == NULL && strtempa == NULL) {
			printf("Files are equal!\n");
			return 0;
		}
		else if (strtempb == NULL) {
			printf("%s is subset of %s\n", argv[2], argv[1]);
			return 0;
		}
		else if (strtempa == NULL) {
			printf("%s is subset of %s\n", argv[1], argv[2]);
			return 0;
		}

	} while (strcmp(strtempa, strtempb) == 0);
	
	fclose(file_a); fclose(file_b);

	printf("Files differ in line #%d:\n%s: %s%s: %s", line, argv[1], strtempa, argv[2], strtempb);
	
	return 0;
}
