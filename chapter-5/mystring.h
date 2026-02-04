#include <stddef.h>

#include "mystring.c"

#ifndef MYSTR
#define MYSTR

char *c_strncpy(char *s, char *t, size_t n);
char *c_strcpy(char *s, char *t);
char *c_strncat(char *s, char *t, size_t n);
char *c_strcat(char *s, char *t);
int c_strncmp(const char *s, const char *t,  size_t n);
int c_strend(char *s, char *t);


#endif
