#include <stddef.h>

#ifndef MYSTR
#define MYSTR

int strcontain(char *list[], char *s);  	// end of list is required to be NULL
char *c_strncpy(char *s, char *t, size_t n);
int c_wordc(char *);
size_t c_maxwlen(char *);
char **c_strtok(char *);
char *c_strcpy(char *s, char *t);
char *c_strncat(char *s, char *t, size_t n);
char *c_strcat(char *s, char *t);
int c_strncmp(const char *s, const char *t,  size_t n);
int c_strend(char *s, char *t);
size_t c_strlen(char *s);


#endif
