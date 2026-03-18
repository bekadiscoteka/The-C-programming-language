
// expectation: sorted array by adding values
/* conops: after each increment 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystd.h"
#include "mystring.h"

#define MAXWORD 100
#define MAXSIZE 10
#define eofstr(str) {str[0] = EOF; str[1] = '\0';}

struct tNode *addNode(struct tNode*, char*);
struct tNode *newNode(char *);
char *c_strdup(char*);
int getword(char*, int);



struct tNode {
	char *word;
	int wc;
	struct tNode *left, 
		    *right;
};


static struct tNode *wordfreq[MAXWORD];
static int wfi = 0;

int nodecmp(const void* a, const void* b) {
	return (*((struct tNode**) b))->wc - (*((struct tNode**) a))->wc;
}

struct tNode *addNode(struct tNode *n, char *s) {
	if (n == NULL) {
		n = newNode(s);	
		wordfreq[wfi++] = n;
		return n;
	}

	int cmpres = strcmp(s, n->word);

	if (cmpres == 0) 
		n->wc += 1;
	else if (cmpres < 0) 
		n->left = addNode(n->left, s);
	else 
		n->right = addNode(n->right, s);
	return n;

}

struct tNode *newNode(char *s) {
	struct tNode *p = (struct tNode*) malloc(sizeof(struct tNode));
	if (p != NULL) {
		p->word = c_strdup(s);	
		p->wc = 1;
		p->left = p->right = NULL;
	}
	return p;
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

	while ( isspace(c=getch()) ) 
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

void treeprint(struct tNode *tp) {
	if (tp == NULL) 
		return;
	treeprint(tp->left);
	printf("%s %d\n", tp->word, tp->wc);
	treeprint(tp->right);
}


int main(void) {
	struct tNode *root = NULL;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF) 
		root = addNode(root, word);

	qsort(wordfreq, wfi, sizeof(void*), nodecmp); 
	printf("printing words in descending order\n");
	for (int i=0; i < wfi; i++) 
		printf("%s %d\n",  (wordfreq[i])->word, (wordfreq[i])->wc);

	return 0;
}




