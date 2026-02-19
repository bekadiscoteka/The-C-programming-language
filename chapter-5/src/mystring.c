#include <stddef.h>
#include "mystring.h"

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



