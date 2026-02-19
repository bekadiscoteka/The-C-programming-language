#ifndef MYSTD
#define MYSTD
#include <stddef.h>

size_t cgetline(char *, size_t);
int catoi(char *);
char *citoa(char *, int);
char *creverse(char *);
ptrdiff_t cstrindex(char *, char);
void cqsort(int[], size_t, size_t);
void string_qsort(char*[], size_t, size_t);
int cstrcmp(char[], char[]);
char *cust_alloc(size_t);
void crelease(char*);
size_t creadlines(char*[], char[], size_t, size_t);
size_t creadlines_alloc(char*[], size_t);
void cwritelines(char*[], size_t);
void push(char);
char pop(void);
int is_empty(void);

#endif
