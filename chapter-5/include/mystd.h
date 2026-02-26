#ifndef MYSTD
#define MYSTD
#include <stddef.h>

size_t cgetline(char *, size_t);
int catoi(char *);
char *citoa(char *, int);
char *creverse(char *);
ptrdiff_t cstrindex(char *, char);
void cqsort(char[], size_t, size_t, int (*) (char, char), int);
void string_qsort(char*[], size_t, size_t, int (*) (char*, char*));
void string_qsort_f(char*[], size_t, size_t, int (*) (char*, char*), int (*) (char));
char *string_filter(char*, int (*) (char));
int cstrcmp(char[], char[]);
int cstrcmp_f(char[], char[]);
int cstrcmp_desc(char[], char[]);
int cstrcmp_desc_f(char[], char[]);
int cintcmp(char[], char[]);
int cintcmp_desc(char[], char[]);
void *cust_alloc(size_t);
void crelease(void*);
size_t creadlines(char*[], char[], size_t, size_t);
size_t creadlines_alloc(char*[], size_t);
void cwritelines(char*[], size_t);
void push(char);
char pop(void);
int is_empty(void);



#endif
