#include "mystd.h"
#include <stdio.h>
#include <ctype.h>
// custom version of standard functions
#define CALLOC_MAXSIZE 10000
#define STACK_MAXSIZE 1000
#define GETCH_MAXBUF 100
#define swap(type, a, b) { \
	type temp = a; \
	a = b; \
	b = temp; \
}

static char calloc_mem[CALLOC_MAXSIZE];
static char *calloc_ptr = calloc_mem;
static char* end = calloc_mem + CALLOC_MAXSIZE;

void *cust_alloc(size_t bytes) {
	if ((calloc_ptr + bytes) < end) {
		register char* ret = calloc_ptr;
		calloc_ptr += bytes;
		return ret;
	}
	else {
		printf("\nERROR on allocation: overflow\n");	
		return NULL;
	}
}

void crelease(void *ptr) {
	if ((void *) calloc_mem <= ptr && ptr < (void *) end) 
		calloc_ptr = ptr;
}

int cstrcmp(char str1[], char str2[]) {
	char a, b;

	while ((a = *str1++) == (b = *str2++)) 
		if (a == '\0' || b == '\0')
			return 0;

	return a - b;
}



int cstrcmp_f(char str1[], char str2[]) {
	char a, b;

	while (tolower(a = *str1++) == tolower(b = *str2++)) 
		if (a == '\0' || b == '\0')
			return 0;

	return a - b;
}


int cstrcmp_desc(char str1[], char str2[]) {
	char a, b;

	while ((a = *str1++) == (b = *str2++)) 
		if (a == '\0' || b == '\0')
			return 0;

	return b - a;
}

int cstrcmp_desc_f(char str1[], char str2[]) {
	char a, b;

	while (tolower(a = *str1++) == tolower(b = *str2++)) 
		if (a == '\0' || b == '\0')
			return 0;

	return b - a;
}



int cintcmp(char str1[], char str2[]) { 
	int a = catoi(str1);
	int b = catoi(str2);

	return a - b; 
}

int cintcmp_desc(char str1[], char str2[]) { 
	int a = catoi(str1);
	int b = catoi(str2);

	return b - a; 
}


size_t cgetline(char arr[], size_t maxsize) {

	char *p = arr;
	for (int c; (c=getchar()) != '\n'; ++p) {
		if (c == EOF) 
			break;
		*p = c;
		if (p-arr >= maxsize-1) {
			*(++p) = '\0';
			return p-arr;
		}
	}

	*p = '\0';
	return p-arr;
}

size_t creadlines(char *lines[], char line[], size_t n, size_t nlines) {

	char *mem, *lineptr=line, *end = line+n;
	int c;

	for (size_t i=0; i < nlines; ++i) {
		if ((lines[i] = mem = lineptr++) >= end) {
			printf("\nAllocation fail: reached the limit\n");
			return i;
		}

		while ((c = getchar()) != '\n') {
			if (c == EOF) {
				*mem = '\0';
				return ++i;
			}

			*mem = c;
			if ((mem = lineptr++) >= end) {
				printf("\nAllocation fail: reached the limit\n");
				lineptr = lines[i];
				return i;
			}
		}
		*mem = '\0';
	}
}
 
size_t creadlines_alloc(char *lines[], size_t nlines) {

	char *mem;
	int c;

	for (size_t i=0; i < nlines; ++i) {
		if ((lines[i] = mem = cust_alloc(1)) == NULL) {
			printf("\nAllocation fail: reached the limit\n");
			return i;
		}

		while ((c = getchar()) != '\n') {
			if (c == EOF) {
				*mem = '\0';
				return ++i;
			}

			*mem = c;
			if ((mem = cust_alloc(1)) == NULL) {
				printf("\nAllocation fail: reached the limit\n");
				crelease(lines[i]);
				return i;
			}
		}
		*mem = '\0';
	}
}

void cwritelines(char *line[], size_t nlines) {
	for (size_t i = 0; i < nlines; ++i) 
		printf("%s\n", line[i]);
}


int catoi(char *a) {
	int n=0, sign=1;
	while (*a == ' ' || *a == '\t')
		a++;

	if (*a == '-') { 
		sign = -1;
		a++;
	}

	for (n=0; isdigit(*a); a++) 
		n = 10 * n + (*a - '0'); 

	return n*sign;
}

char *citoa(char *arr, int i) {
	char *a = arr;
	int sign = 1;

	if (i < 0) {
		sign = -1;
		i *= -1;
	}

	do {
		*a++ = i%10 + '0';
		i /= 10;
	}
	while (i != 0); 

	if (sign < 0)
		*a++ = '-';

	*a = '\0';

	return creverse(arr);
}


char *creverse(char *a) {
	char *ret = a, *begin = a;

	while (*a != '\0')
		a++;

	for (--a; begin < a; begin++, --a) 
		swap(char, *begin, *a)

	return ret; 
}	

ptrdiff_t cstrindex(char *a, char t) {

	for (char *p = a; *p != '\0'; p++) 
		if (*p == t) 
			return p - a;

	return -1;

}

void cqsort(char arr[], size_t left, size_t right, 
		int (*comp) (char, char), int desc) {
	if (left < right) {
		size_t storeIndex = left+1;	
		for (int i=left; i >= left && i < right; ++i) {
			if (desc > 0) {
				if ((*comp)(arr[i], arr[left]) > 0) {
					swap(char, arr[storeIndex], arr[i])
					storeIndex++;
				}	
			}
			else { 
				if ((*comp)(arr[i], arr[left]) < 0) {
					swap(char, arr[storeIndex], arr[i])
					storeIndex++;
				}
			}
		}	
		swap(char, arr[storeIndex-1], arr[left])
		cqsort(arr, left, storeIndex-1, *comp, desc); 
		cqsort(arr, storeIndex, right, *comp, desc);
	}
}

char *string_filter(char *s, int (*filter) (char)) {
	char *ns = cust_alloc(1);
	char *ret = ns;
	char a;
	while ((a = *s++) != '\0') {
		if ((*filter)(a)) {
			*ns = a;
			ns = cust_alloc(1);
		}
	} 

	*ns = '\0';
	return ret; 
}

void string_qsort( char *arr[], size_t left, size_t right, 
		int (*comp)(char*, char*) ) {
	if (left < right) {
		size_t storeIndex = left+1;	
		for (size_t i=left+1; i >= left && i < right; ++i) {
			if ((*comp)(arr[left], arr[i]) > 0) { 
				swap(char*, arr[storeIndex], arr[i])
				storeIndex++;
			}	
		}	
		swap(char*, arr[storeIndex-1], arr[left])
		string_qsort(arr, left, storeIndex-1, comp), string_qsort(arr, storeIndex, right, comp);
	}
}

void string_qsort_f( char *arr[], size_t left, size_t right, // with filter for cmp
		int (*comp)(char*, char*), int (*filter) (char)) {
	if (left < right) {
		size_t storeIndex = left+1;	
		for (size_t i=left+1; i >= left && i < right; ++i) {
			char *a = string_filter(arr[left], filter);
			char *b = string_filter(arr[i], filter);
			if (((*comp)(a, b)) > 0) { 
				swap(char*, arr[storeIndex], arr[i])
				storeIndex++;
			}	
			crelease(a);
		}	
		swap(char*, arr[storeIndex-1], arr[left])
		string_qsort_f(arr, left, storeIndex-1, comp, filter);
		string_qsort_f(arr, storeIndex, right, comp, filter);
	}
}

static char stack[STACK_MAXSIZE];
static char *stackp = stack;

void push(char pushval) {
	if (stackp - stack <= STACK_MAXSIZE) 
		*stackp++ = pushval;
	else 
		printf("\ncharstack overflow\n");
}

char pop(void) {
	if (stackp == stack) {
		printf("\ncharstack is empty\n");
		return '\0';
	}
	else 
		return *--stackp;
}

int is_empty(void) {
	return stackp == stack;
}

char getch_buf[GETCH_MAXBUF];
size_t getch_bufi;

char getch(void) {
	if (getch_bufi > 0) 
		return getch_buf[--getch_bufi];	
	else 
		return getchar();
}

void ungetch(char c) {
	if (getch_bufi < GETCH_MAXBUF) 
		getch_buf[getch_bufi++] = c;
	else 
		printf("\ngetch buffer overflow\n");
}



