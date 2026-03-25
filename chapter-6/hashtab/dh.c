/*
*//*  define hash table program
*//*  ------------------------	
*//*  
*//*
*/

#include "hash.h"
#include "mystd.h"
#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100


int getword_local(char *word, int lim) 
{ 
   int c; 
   char *w = word; 

	while ( (c=getch()) == ' ' || c == '\t' ) 
		;

   if (c != EOF) 
	   *w++ = c; 


   if (!isalpha(c) && c != '_') { 
	   *w = '\0'; 
	   return c; 
   } 

   for ( ; --lim > 0; w++) 
	   if ( !isalnum(*w = getch()) && !(*w == '_') ) { 
		   ungetch(*w); 
		   break; 
	   } 
   *w = '\0'; 
   return word[0]; 
}

int main(void) {

	char word[MAXWORD];
	char c;
	while ((c=getword_local(word, MAXWORD)) != EOF) {

		if (c == '#') {
			c = getword_local(word, MAXWORD);
			if (strcmp(word, "define") == 0) {
				if (getword_local(word, MAXWORD) == '\n') {
					printf("not enough argument of define\n");
					continue;	
				}
				char *name = c_strdup(word);
				if (getword_local(word, MAXWORD) == '\n') {
					printf("not enough argument of define\n");
					continue;	
				}			
				char *def = c_strdup(word);
				c_install(name, def);

				free(name);
				free(def);
			}
			else if (strcmp(word, "undef") == 0) {
				if (getword_local(word, MAXWORD) == '\n') {
					printf("not enough argument of define\n");
					continue;	
				}
				undef(word);
			}
			else 
				printf("%s is not a macro\n", word);
		}

		else if (c == '\n')
			putchar('\n');

		else if (word[1] == '\0' && !isalpha(c)) 
			continue;
		else {
			const char *temp;
			if ((temp=c_lookup(word)) == NULL) {
				printf("%s ", word);
				continue;
			}
			printf("%s ", temp); 
		}

	}
}
