#include <stddef.h>
#include <string.h>
#include "mystring.h"
#include "mystd.h"
#include <ctype.h>
#define CHAR 'c'
#define BLANK ' '
#define UNDEF 0

char *c_strncpy(char *s, char *t, size_t n) {
	char *ret = s;
	while (n-- > 0)	{
		if ((*s++ = *t++) == '\0') {
			while (n-- > 0) 
				*s++ = '\0';
			break;
		}
	}
	return ret;
}

int strcontain(char *list[], char *s) {
	char *temp;
	while ((temp = *list++) != NULL)
		if (cstrcmp(temp, s) == 0)
			return 1;
	return 0;
}

int c_wordc(char *s) {
	char state = UNDEF;
	int n=0;

	while (*s != '\0') {
		switch (state) {
			case CHAR:
			   if (isblank(*s++))
			   		state = BLANK;
			   break;
			case BLANK: 
			   if (!isblank(*s++)) { 
				   state = CHAR;
				   n++;
			   }
			   break;
			default:
				if (isblank(*s)) 
					state = BLANK;
				else {
					state = CHAR;
					n++;
				}
				break;
		}
	}
	
	return n;
}

size_t c_maxwlen(char *s) {
	char state = isblank(*s) ? BLANK : CHAR;
	int n=0, maxn=0;
	
	while (*s != '\0') 
	{
		switch (state) {
			case CHAR:
				if (isblank(*s)) {
					maxn = n > maxn ? n : maxn;			
					state = BLANK;
					n=0;
				}
				else { 
					n++;
					s++;
				}
				break;

			case BLANK: 
				if (isblank(*s)) 
					s++;
				else 
					state = CHAR;
				break;
		}
	}
	if (state == CHAR) 
		maxn = n > maxn ? n : maxn;			
	
	return maxn;
}	

char **c_strtok(char *s) {
	char state = UNDEF;
	int itoken=0, istr=0;
	size_t maxwlen = c_maxwlen(s);

	char **tokens = cust_alloc((c_wordc(s) + 1) * sizeof(void *));

	while (*s != '\0') {
		switch (state) {
			case CHAR:
				if (isblank(*s)) {
					state = BLANK;
					tokens[itoken++][istr] = '\0';
					istr = 0;
				}
				else 
					tokens[itoken][istr++] = *s++;
				break;
			case BLANK:
				if (isblank(*s)) 
					s++;
				else { 
					state = CHAR;
					tokens[itoken] = cust_alloc(maxwlen+1);
				}
				break;
			default: 
				if (isblank(*s)) 
					state = BLANK;
				else { 
					state = CHAR;
					tokens[itoken] = cust_alloc(maxwlen+1);
				}
				break;
		}	
				
	}

	if (state == CHAR)  
		tokens[itoken++][istr] = '\0';

	tokens[itoken] = NULL;

	return tokens; 
}


size_t c_strlen(char s[]) {
	char *sp = s;	
	while (*sp != '\0') 
		sp++;
	
	return sp - s;	
}

char *c_strncat(char *s, char *t, size_t n) {
	char *ret = s;
	while (*s != '\0')
		s++;
	
	c_strncpy(s, t, n);
	return ret;
}	

int c_strncmp(const char *s, const char *t, size_t n) {
	for (int i=0; i < n; s++, t++, i++)	{
		if (*s > *t) 
			return 1;
		else  if (*s < *t)
			return -1;

		if (*s == '\0')
			break;
	}
	
	return 0;
}

char *c_strcat(char *s, char *t) {
	char *ret = s;
	while (*s++ != '\0') 
		;	
	for (--s; *s = *t; ++t, ++s)
		;	

	return ret;
}

int c_strend(char *s, char *t) {
	size_t s_len=0, t_len=0;
	
	while (s[s_len] + t[t_len]) {
		if (s[s_len]) s_len++;
		if (t[t_len]) t_len++;
	}

	if (s_len > t_len) 
		for (s += (s_len - t_len); *s == *t; ++s, ++t)
			if (*t == '\0') 
				return 1;

	return 0;
}

char *c_strcpy(char *d, char *s) {
	char *ret = d;
	while ((*d++ = *s++) != '\0')
		;

	return ret;
}



