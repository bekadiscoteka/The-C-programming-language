#include <stdio.h>
#include <ctype.h>
#include "mystd.h"
#include "mystring.h"
#define MAXLINE 100
#define MAXRULE 5
#define MAXSIZE 100
#define MAXFLAGS 5

static char cfields[MAXRULE][MAXSIZE];
static char cflags[MAXRULE][MAXFLAGS];
static int cli = 0;

char *getfield(char *s, int i) {
	int n = catoi(cfields[i])-1;
	if (c_wordc(s) < n+1) 
		return NULL;


	char** tok = c_strtok(s);


	char temp[c_strlen(tok[n])+1];

	c_strcpy(temp, tok[n]);

	crelease((void*) tok);

	return c_strcpy(cust_alloc(c_strlen(temp)), temp);
}

int field_cstrcmp(char* str1, char* str2) {
	int nrule=0; // starting from primary rule
	int ret;

	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, nrule)) == NULL)
			return -1; 
		if ((nstr2 = getfield(str2, nrule)) == NULL)
			return 1;
		++nrule;
	}
	while ( (ret = cstrcmp(nstr1, nstr2)) == 0 && nrule < cli);
	return ret;
}



int field_cstrcmp_f(char str1[], char str2[]) {

	int i=0;
	int ret;
	printf("\nnew call\n");
	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, i)) == NULL)
			return -1; 
		if ((nstr2 = getfield(str2, i)) == NULL)
			return 1;
		++i;
	}
	while ( (ret = cstrcmp_f(nstr1, nstr2)) == 0 && i < cli);
	return ret;
}


int field_cstrcmp_desc(char str1[], char str2[]) {

	int i=0;
	int ret;

	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, i)) == NULL)
			return 1; 
		if ((nstr2 = getfield(str2, i)) == NULL)
			return -1;
		++i;
	}
	while ( (ret = cstrcmp_desc(nstr1, nstr2)) == 0 && i < cli);
	return ret;
}

int field_cintcmp(char str1[], char str2[]) { 
	int i=0;
	int ret;

	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, i)) == NULL)
			return -1; 
		if ((nstr2 = getfield(str2, i)) == NULL)
			return 1;		
		++i;
	}
	while ( (ret = cintcmp(nstr1, nstr2)) == 0 && i < cli);
	return ret;
}

int field_cintcmp_desc(char str1[], char str2[]) { 

	int i=0;
	int ret;

	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, i)) == NULL)
			return 1; 
		if ((nstr2 = getfield(str2, i)) == NULL)
			return -1;
		++i;
	}
	while ( (ret = cintcmp_desc(nstr1, nstr2)) == 0 && i < cli);
	return ret;
}

int field_cstrcmp_desc_f(char str1[], char str2[]) {
	int i=0;
	int ret;

	char *nstr1, *nstr2;
	do {
		if ((nstr1 = getfield(str1, i)) == NULL)
			return 1; 
		if ((nstr2 = getfield(str2, i)) == NULL)
			return -1;
		++i;
	}
	while ( (ret = cstrcmp_desc_f(nstr1, nstr2)) == 0 && i < cli);
	return ret;
}



int charcmp(char a, char b) {
	return a - b;
}

int charcmp_f(char a, char b) {
	return tolower(a) - tolower(b);
}

int d_filter(char c) {
	if (isalpha(c) || isdigit(c) || isspace(c)) 
		return 1;
	return 0;
}

char f_filter(char c) {
	return (char) tolower(c);
}

int df_filter(char c) {
	return d_filter(tolower(c));
}

int buffer(char c) {
	return 1;
}


int main(int argc, char *argv[]) {
	int n=0, r=0, f=0, d=0;
	int (*cmp_ptr) (char*, char*) = cstrcmp;
	int (*filter_ptr) (char) = buffer;

	while (--argc > 0) {
		char *arg;
		switch (*(arg = *++argv)) {
			case '-':
				switch (*(++arg)) {
					case 'n':
						// comparing numbers
						n++;
						break;
					case 'r':
						r++;
						break;
					case 'f':
						f++;
						break;
					case 'd':
						d++;
						break;
					default:
						if (isdigit(*arg)) {
							int i=0, j=0;
							while (isdigit(*arg)) 
								cfields[cli][i++] = *arg++;
							cfields[cli][i] = '\0';
							while (*arg != '\0') 
								cflags[cli][j++] = *arg++;	
							cflags[cli++][j] = '\0';	
						}
						else 
							printf("\nno such parameter -%s", arg-1);
						break;
				}
				break;
			default:
				printf("\nundefined argument %s\n", arg);
				break;
		}
	}

	if (n) 
		if (r) 
			cmp_ptr = cintcmp_desc;
		else 
			cmp_ptr = cintcmp;

	else { 
		if (r) {
			if (f)
				cmp_ptr = cstrcmp_desc_f;
			else 
				cmp_ptr = cstrcmp_desc;
		}
		else {
			if (f) 
				cmp_ptr = cstrcmp_f;
			else 
				cmp_ptr = cstrcmp;
		}
	}


	if (d & f) 
		filter_ptr = df_filter; 
	else if (d) 
		filter_ptr = d_filter; 
	if (f) { 
		if (r) 
			cmp_ptr = cstrcmp_desc_f;
		else 
			cmp_ptr = cstrcmp_f;
	}
	
	
	char *lines[MAXLINE];
	size_t lines_n;
	if (cli > 0) {
		r = cstrindex(cflags[0], 'r');
		f = cstrindex(cflags[0], 'f');
		d = cstrindex(cflags[0], 'd');
		n = cstrindex(cflags[0], 'n');
		
		int (*cmp) (char, char);

		if (n >= 0) 
			if (r >= 0) 
				cmp_ptr = field_cintcmp_desc;
			else 
				cmp_ptr = field_cintcmp;

		else { 
			if (r >= 0) {
				if (f >= 0)
					cmp_ptr = field_cstrcmp_desc_f;
				else 
					cmp_ptr = field_cstrcmp_desc;
			}
			else {
				if (f >= 0) 
					cmp_ptr = field_cstrcmp_f;
				else 
					cmp_ptr = field_cstrcmp;
			}
		}


		if (d >= 0 & f >= 0) 
			filter_ptr = df_filter; 
		else if (d) 
			filter_ptr = d_filter; 
		if (f >= 0) { 
			if (r >= 0) 
				cmp_ptr = field_cstrcmp_desc_f;
			else 
				cmp_ptr = field_cstrcmp_f;
		}

	}	

	while ((lines_n = creadlines_alloc(lines, MAXLINE)) > 0) {
		string_qsort_f(lines, 0, lines_n, cmp_ptr, filter_ptr);
		cwritelines(lines, lines_n);
		printf("\nWould you like to continue? (y/n):");
		switch (getchar()) {
			case 'n':
				goto finish;
				break;	  
			default:
				break;
		}
	}

finish: 
	printf("\nprogram is finished\n");
	return 0;
	
}
