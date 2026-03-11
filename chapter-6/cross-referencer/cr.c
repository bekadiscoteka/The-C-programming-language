#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystd.h"
#include "mystring.h"

#define MAXWORD 100
#define MAXSIZE 10
#define eofstr(str) {str[0] = EOF; str[1] = '\0';}

struct tNode *addNode(struct tNode*, char*, int);
struct tNode *newNode(char *, int);
void treeprint(struct tNode*);
static void treeprint_intern(struct tNode*);
char *c_strdup(char*);
int getword(char*, int);


struct tNode {
	char *word;
	int *lines;
	int linesi;	
	struct tNode *left, 
		    *right;
};

struct tNode *addNode(struct tNode *n, char *s, int line) {
	if (n == NULL) {
		n = newNode(s, line);	
		return n;
	}

	int cmpres = strcmp(s, n->word);

	if (cmpres == 0) 
		(n->lines)[(n->linesi)++] = line;
	else if (cmpres < 0) 
		n->left = addNode(n->left, s, line);
	else 
		n->right = addNode(n->right, s, line);
	return n;

}

struct tNode *newNode(char *s, int line) {
	struct tNode *p = (struct tNode*) malloc(sizeof(struct tNode));
	if (p != NULL) {
		p->word = c_strdup(s);	
		p->left = p->right = NULL;
		p->linesi = 0;
		p->lines = malloc(sizeof(int) * MAXSIZE);
		p->lines[(p->linesi)++] = line;
	}
	return p;
}

void treeprint(struct tNode *tp) {
	if (tp == NULL) 
		return;
	treeprint(tp->left);
	printf("%s \t", tp->word);
	for (int i=0; i < (tp->linesi); ++i) 
		printf("%d ", tp->lines[i]);
	putchar('\n');
	treeprint(tp->right);
}



char *c_strdup(char *s) {
	char *ret;
	if ( strlen(s) > 0 && (ret = (char*) malloc(strlen(s) + 1)) ) {
		strcpy(ret, s);
		return ret;
	}

	return NULL;
}


int getword(char *word, int lim) 
{ 
   int c; 
   char *w = word; 
   while ((c = getch()) == ' ' || c == '\t')
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
	struct tNode *root = NULL;
	char word[MAXWORD];
	int line=0;
	printf("welcome to prgr\n");
	while (getword(word, MAXWORD) != EOF) {
		if (word[0] == '\n') 
			line++;
		else 
			root = addNode(root, word, line);	
	}
	treeprint(root);
	return 0;
}




