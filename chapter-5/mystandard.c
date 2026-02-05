#include "mystandard.h"
#include <stddef.h>

#define swap(type, a, b) \
	type temp = a; \
	a = b; \
	b = temp;

char *cgetline(char arr[], size_t maxsize) {

	for (int c, *p=arr; (c=getchar()) != '\n'; ++p) {
		if (c == EOF) 
			break;
		*p = c;
		if (p-arr < maxsize-1) {
			*(++p) = '\0';
			return arr;
		}
	}

	*p = '\0';
	return arr;
}

int catoi(char *a) {
	int n;
	for (n=0; isdigit(*a); a++) 
		n = 10 * n + (*a - '0'); 

	return n;
}

char *citoa(char *arr; int i) {
	char *a = arr;	
	for (*a++ = '\0'; i / 10; ++a, i /= 10) 
		*a = (i % 10) + '0';
	*a = '\0';
	
	return reverse(arr);
}


char *creverse(char *a) {
	char *ret = a, *begin = a;

	while (*a)
		a++;

	for (; begin < a; begin++, --a) 
		swap(char, *begin, *a);

	return ret; 
}	

ptrdiff_t cstrindex(char *a, char t) {

	for (char *p = a; *p != '\0'; p++) 
		if (*p == t) 
			return p - a;

	return -1;

}

