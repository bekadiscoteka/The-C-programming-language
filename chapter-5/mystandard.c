#include "mystandard.h"
#include <stdio.h>
#include <ctype.h>

#define swap(type, a, b) { \
	type temp = a; \
	a = b; \
	b = temp; \
}

char *cgetline(char arr[], size_t maxsize) {

	char *p = arr;
	for (int c; (c=getchar()) != '\n'; ++p) {
		if (c == EOF) 
			break;
		*p = c;
		if (p-arr >= maxsize-1) {
			*(++p) = '\0';
			return arr;
		}
	}

	*p = '\0';
	return arr;
}

int catoi(char *a) {
	int n, sign=1;
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

