#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mystd.h"
#include "mystring.h"

#define MAXWORD 100
#define eofstr(str) {str[0] = EOF; str[1] = '\0';}

static int N_PARAM = 3;

struct tNode {
	char *s;
	struct tNode *left;
	struct tNode *right;
	struct tNode *pleft; 			// for print
	struct tNode *pright;
};


struct tNode *addNode(struct tNode*, char*);
struct tNode *newNode(char *);
void treeprint(struct tNode*);
static void treeprint_intern(struct tNode*);
char *c_strdup(char*);
int getword(char*, int);



struct tNode *addNode(struct tNode *n, char *s) {
	if (n == NULL) {
		n = newNode(s);	
		return n;
	}

	int ncmpres = strncmp(s, n->s, N_PARAM);
	int cmpres = strcmp(s, n->s);

	if (ncmpres == 0) {
		if (cmpres == 0 || cmpres < 0) 
			n->pleft = addNode(n->pleft, s);
		else 
			n->pright = addNode(n->pright, s);
	}

	else if (ncmpres < 0) 
		n->left = addNode(n->left, s);
	else
		n->right = addNode(n->right, s);
	
	return n;

}

struct tNode *newNode(char *s) {
	struct tNode *p = (struct tNode*) malloc(sizeof(struct tNode));
	if (p != NULL) {
		p->s = c_strdup(s);	
		p->left = p->right = p->pleft = p->pright = NULL;
	}
	return p;
}

char *c_strdup(char *s) {
	char *rs;
	if ((rs = (char*) malloc(strlen(s) + 1)) != NULL) 
		strcpy(rs, s);
	return rs;
}

static void treeprint_intern(struct tNode *tp) {
	if (tp == NULL) 
		return;
	treeprint_intern(tp->pleft);
	printf("%s ", tp->s);
	treeprint_intern(tp->pright);
}

void treeprint(struct tNode *tp) {
	if (tp == NULL) 
		return;
	treeprint(tp->left);
	treeprint_intern(tp->pleft);
	printf("%s ", tp->s);
	treeprint_intern(tp->pright);
	putchar('\n');
	treeprint(tp->right);
}

int getword(char *word, int lim) 
{ 
   int c; 
   char *w = word; 
   while (isspace(c = getch())) 
	   ; 
   if (c != EOF) 
	   *w++ = c; 

   switch (c) {
	   case '#':
		   while ((c=getch()) != '\n') {
			   if (c == EOF) {
				   eofstr(word);
				   return EOF;
			   }
			   else if (c == '\\') 
				   getch(); // skip the next character
		   }

		   return getword(word, lim);

	   case '/':
		  if ((c=getch()) == '/') {
			 while ((c=getch()) != '\n')
				if (c == EOF) {
					eofstr(word);
					return EOF; 
				}
			 return getword(word, lim);
		  }
		  else if (c == '*') {
			  while (1) {
				  if (c == EOF) {
					  eofstr(word);
					  return EOF;
				  }
				  else if ((c=getch()) == '*') {
				
					  if ((c=getch()) == '/')
					      return getword(word, lim);  
					  else 
						  ungetch(c);
				  }
			  }
			  	
			  
		  }
		  ungetch(c);
		  break;
	   case '\"':
		  while ((c=getch()) != '\"') {
			  if (c == EOF) {
				  eofstr(word);
				  return EOF;
			  }
			  else if (c == '\\')
				  getch();
		  }
		  return getword(word, lim);
	   case '\'':
		  while ((c=getch()) != '\'') {
			  if (c == EOF) {
				  eofstr(word);
				  return EOF;
			  }

			  else if (c == '\\') 
				  getch();
		  }
		  return getword(word, lim);
   }


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

int main(int argc, char *argv[]) {
	int param;
	while (--argc > 0) {
		if ((param = atoi((++argv)[0])) > 0) {
			N_PARAM = param; 
			break;	
		}
	}

	printf("n = %d\n", N_PARAM);
	struct tNode *root = NULL;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF) 
		root = addNode(root, word);	
	treeprint(root);
	return 0;
}
