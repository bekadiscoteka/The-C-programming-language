// doesn't consider the last line, without enter
#include <stdio.h>
#define MAXSIZE 100
#define TABSTOP 8

#define BLANK_IN 1
#define BLANK_OUT 0

void entab(char dest_str[], char src_str[], int tabstop);
int l_getline(char arr[], int size);

void main(void) {
	char line[MAXSIZE], entab_arr[MAXSIZE];
	int size;

	while ((size=l_getline(line, MAXSIZE)) > 0) {
		if (line[0] != '\n') {
			entab(entab_arr, line, TABSTOP);
			printf("%s\n", entab_arr);
		}
	}
	
}

void entab(char dest[], char src[], int tabstop) {
	int state=BLANK_OUT, i_src=0, i_dest=0, blank_counter=0;
	
	while (src[i_src] != '\0') {
		if (src[i_src] == ' ') {

			blank_counter=0;

			while (src[i_src] == ' ') {
				++blank_counter;
				++i_src;

				if (i_src % tabstop == 0) {
					dest[i_dest++] = '\t';
					blank_counter = 0;
				}

			}

			while (blank_counter > 0) {
				dest[i_dest++] = ' ';
				--blank_counter;
			}

		}

		else 
			dest[i_dest++] = src[i_src++];
	}

	dest[i_dest++] = '\0';
}


int l_getline(char arr[], int size) {
	int c, i;
	
	for (i=0; (c=getchar()) != '\n' && i < size-1; ++i) {
		if (c == EOF) 
			return 0;
		else 
			arr[i] = c;
	}

	arr[i++] = '\n';
	arr[i] = '\0';

	return i;
}






